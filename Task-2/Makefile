CFILES := $(wildcard ./src/*.c)
OFILES = $(CFILES: ./src/%.c = ./obj/%.o)
OBJFILES = ./obj/boot.o ./obj/kernel.o ./obj/uart0.o ./obj/uart1.o ./obj/mbox.o ./obj/framebf.o ./obj/timer.o
GCCFLAGS := -Wall -O2 -ffreestanding -nostdlib -nostdinc

all: clean $(OBJFILES) ./obj/kernel8.img 

# boot
./obj/boot.o: ./src/boot.S
	aarch64-none-elf-gcc $(GCCFLAGS) -c ./src/boot.S -o ./obj/boot.o 
./obj/%.o: ./src/%.c
	aarch64-none-elf-gcc $(GCCFLAGS) -c $< -o $@

# uart0xc 
./obj/uart0.o: ./src/uart/uart0.c
	aarch64-none-elf-gcc $(GCCFLAGS) -c ./src/uart/uart0.c -o ./obj/uart0.o 

# uart1
./obj/uart1.o: ./src/uart/uart1.c
	aarch64-none-elf-gcc $(GCCFLAGS) -c ./src/uart/uart1.c -o ./obj/uart1.o 

#timer
./timer/timer.o: ./src/timer/timer.c
	aarch64-none-elf-gcc $(GCCFLAGS) -c ./src/timer/timer.c -o ./obj/timer.o
# mbox
./obj/mbox.o: ./src/mbox/mbox.c
	aarch64-none-elf-gcc $(GCCFLAGS) -c ./src/mbox/mbox.c -o ./obj/mbox.o 

# frame buffer
./obj/framebf.o: ./src/framebf/framebf.c
	aarch64-none-elf-gcc $(GCCFLAGS) -c ./src/framebf/framebf.c -o ./obj/framebf.o 

# kernel
./obj/kernel.o: ./src/kernel.c
	aarch64-none-elf-gcc $(GCCFLAGS) -c ./src/kernel.c -o ./obj/kernel.o 

./obj/kernel8.img: ./obj/boot.o $(OFILES)
# aarch64-none-elf -nostdlib $(OFILES) -T ./src/link.ld -o ./obj/kernel8.elf
# aarch64-none-elf-ld -nostdlib $(OBJFILES) -T ./src/link.ld -o ./obj/kernel8.elf
	
	aarch64-none-elf-ld -nostdlib $(OBJFILES) -T ./src/link.ld -o ./obj/kernel8.elf
	aarch64-none-elf-objcopy -O binary ./obj/kernel8.elf ./obj/kernel8.img

clean:
	del .\obj\*.o .\obj\*.img .\obj\kernel8.elf .\obj\kernel8.img
	
run:
	qemu-system-aarch64 -M raspi3 -kernel ./obj/kernel8.img -serial stdio -serial null
