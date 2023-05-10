movq $0x3e52dff5,%rdi
movq $0x55629f28,%rdi
retq


0000000000000000 <.text>:
   0:	48 c7 c7 f5 df 52 3e 	mov    $0x3e52dff5,%rdi
   7:	48 c7 c4 28 9f 62 55 	mov    $0x55629f28,%rsp
   e:	c3                   	retq 


   0000000000000000 <.text>:
   0:	48 c7 c7 f5 df 52 3e 	mov    $0x3e52dff5,%rdi
   7:	c3                   	retq 

~~

   55629F50

   000000000000000 <.text>:
   0:	48 c7 c7 50 9f 62 55 	mov    $0x55629f50,%rdi
   7:	c3                   	retq


~~


   00000000004019d4 <setval_159>:   4019D9
  4019d4:	c7 07 75 ac 31 58    	movl   $0x5831ac75,(%rdi)
  4019da:	c3                   	ret    

  00000000004019e8 <getval_404>:    4019EA
  4019e8:	b8 34 48 89 c7       	mov    $0xc7894834,%eax
  4019ed:	c3                   	ret 