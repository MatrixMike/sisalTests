/usr/local/libexec/sisal/sisal -dir /usr/local/share/sisal hello.sis -O hello.if1 -Fhello.sis 
/usr/local/libexec/sisal/if1ld -o hello.mono -w -FUR hello.if1 
/usr/local/libexec/sisal/if1opt hello.mono hello.opt -Y -G -6 -R -M -1 -l -e -U2 
/usr/local/libexec/sisal/if2mem hello.opt hello.mem 
/usr/local/libexec/sisal/if2up hello.mem hello.up -I 
/usr/local/libexec/sisal/if2part /usr/local/share/sisal/s.costs hello.up hello.part - - 
/usr/local/libexec/sisal/if2gen hello.part hello.c -m -U -B -G -O -a -Y3 
/usr/bin/gcc hello.c -c -o hello.o -I/usr/local/include/sisal -g -O2 
/usr/bin/gcc -o s.out /usr/local/lib/sisal/srt0.o hello.o -L/usr/local/lib/sisal -lsisal -pthread -lm 
