// Noah Hanks, nhanks10

#include "cachelab.h"
#include <getopt.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long int memAddress;

// struct for holding the parameters of the cache
struct Parameters {
    int s; // number of set index bits
    int S; // number of sets
    int E; // number of lines per set
    int b; // block bits
    int B; // block size
    int hits;
    int misses;
    int evicts;
    int verbose;
};

// struct for holding the lines of the cache
struct setLine {
    int uses;
    int valid;
    unsigned long long tag;
    char *block;
};

// struct for holding the sets of the cache
struct cacheSet {
    struct setLine *lines;
};

// struct for holding the cache
struct Cache {
    struct cacheSet *sets;
};

// function prototypes
struct Cache build(long long totalSets, int totalLines, int blockSize) {
    struct Cache newCache = {.sets = NULL};

    newCache.sets = malloc(sizeof(struct cacheSet) * totalSets);

    for (int i = 0; i < totalSets; i++) {
        newCache.sets[i].lines = malloc(sizeof(struct setLine) * totalLines);
        for (int j = 0; j < totalLines; j++)
            newCache.sets[i].lines[j] = (struct setLine){.uses = 0, .valid = 0, .tag = 0};
    }

    return newCache;
}

// prints the usage of the program
void printUsage() {
    printf("Usafe: /csim-ref [-hv] -s <s> -E <E> -b <b> -t <tracefile>\n");
    printf("-h: Optional help flag that prints usage info\n");
    printf("-v: Optional verbose flag that displays trace info\n");
    printf("-s <s>: Number of set index bits (the number of sets is 2^s)\n");
    printf("-E <E>: Associativity (number of lines per set)\n");
    printf("-b <b>: Number of block bits (the block size is 2^b)\n");
    printf("-t <tracefile>: Name of the valgrind trace to replay\n");
}

// prints the summary of the cache simulation
int findLRU(struct cacheSet set, struct Parameters param) {
    int totalLines = param.E;
    int minUses = set.lines[0].uses;
    int LRU = 0;

    // finds the line with the least uses
    for (int i = 0; i < totalLines; i++) {
        if (set.lines[i].uses < minUses) {
            LRU = i;
            minUses = set.lines[i].uses;
        }
    }
    return LRU;
}

// finds the line with the most uses
int findMRU(struct cacheSet set, struct Parameters param) {
    int maxUses = set.lines[0].uses;
    int MRU = 0;

    for (int i = 1; i < param.E; i++)
        if (set.lines[i].uses > maxUses) {
            MRU = i;
            maxUses = set.lines[i].uses;
        }

    return MRU;
}

// checks if a given line is a hit
int checkHit(struct setLine line, memAddress address) { return line.tag == address && line.valid; }

// checks if a given set is full
int isSetFull(struct cacheSet set, struct Parameters param) {
    for (int i = 0; i < param.E; i++)
        if (set.lines[i].valid == 0)
            return 1;
    return 0;
}

// checks if a given set has any empty lines
int anyEmptyLines(struct cacheSet set, struct Parameters param) {
    for (int i = 0; i < param.E; i++)
        if (set.lines[i].valid == 0)
            return i;
    return 0;
}

struct Parameters Simulation(struct Cache cache_A, struct Parameters param, memAddress address) {
    int tagSize = 64 - (param.b + param.s);
    memAddress addressTag = address >> (param.s + param.b);
    unsigned long long setNum = (address << (tagSize)) >> (tagSize + param.b);

    struct cacheSet set = cache_A.sets[setNum];
    int hit = 0;

    for (int i = 0; i < param.E; i++) {
        if (checkHit(set.lines[i], addressTag)) {
            param.hits++;
            hit = 1;
            cache_A.sets[setNum].lines[i].uses =
                cache_A.sets[setNum].lines[findMRU(set, param)].uses + 1;
            break;
        }
    }

    if (hit == 0 && isSetFull(set, param) == 1) {
        param.misses++;
        int emptyLine = anyEmptyLines(set, param);
        set.lines[emptyLine].tag = addressTag;
        set.lines[emptyLine].valid = 1;
        cache_A.sets[setNum].lines[emptyLine].uses =
            cache_A.sets[setNum].lines[findMRU(set, param)].uses + 1;
    } else if (hit == 0) {
        param.misses++;
        param.evicts++;
        int LRU = findLRU(set, param);
        set.lines[LRU].tag = addressTag;
        cache_A.sets[setNum].lines[LRU].uses =
            cache_A.sets[setNum].lines[findMRU(set, param)].uses + 1;
    }

    return param;
}

// clears the cache
void clearCache(struct Cache cache_A, long long totalSets, int totalLines, long long blockSize) {
    for (int i = 0; i < totalSets; i++) {
        if (cache_A.sets[i].lines)
            free(cache_A.sets[i].lines);
    }
    if (cache_A.sets)
        free(cache_A.sets);
}

int main(int argc, char **argv) {
    struct Cache simulatedCache;
    struct Parameters param;
    long long totalSets;
    long long blockSize;

    char *traceFile;
    char c;

    while ((c = getopt(argc, argv, "s:E:b:t:vh")) != -1) {
        switch (c) {
        case 's':
            param.s = atoi(optarg);
            break;
        case 'E':
            param.E = atoi(optarg);
            break;
        case 'b':
            param.b = atoi(optarg);
            break;
        case 't':
            traceFile = optarg;
            break;
        case 'v':
            param.verbose = 1;
            break;
        case 'h':
            printUsage();
            exit(0);
        default:
            printUsage();
            exit(0);
        }
    }

    totalSets = pow(2.0, param.s); // get Number of set by 2^s
    blockSize = pow(2.0, param.b); // get blockSize by 2^b

    param.hits = 0;
    param.misses = 0;
    param.evicts = 0;

    simulatedCache = build(totalSets, param.E, blockSize);

    FILE *openTrace;
    char instruction;
    memAddress address;
    int size;

    openTrace = fopen(traceFile, "r");
    if (openTrace != NULL) {
        while (fscanf(openTrace, " %c %llx,%d", &instruction, &address, &size) == 3) {
            switch (instruction) {
            case 'I':
                break;
            case 'L':
                param = Simulation(simulatedCache, param, address);
                break;
            case 'S':
                param = Simulation(simulatedCache, param, address);
                break;
            case 'M':
                param = Simulation(simulatedCache, param, address);
                param = Simulation(simulatedCache, param, address);
                break;
            default:
                break;
            }
        }
    }
    printSummary(param.hits, param.misses, param.evicts);
    clearCache(simulatedCache, totalSets, param.E, blockSize);
    fclose(openTrace);
    return 0;
}