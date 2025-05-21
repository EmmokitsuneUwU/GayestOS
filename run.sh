export PATH=$PATH:/usr/local/i386elfgcc/bin

nasm "Src/ASM/boot.asm" -f bin -o "Binaries/boot.bin"
nasm "Src/ASM/kernel_entry.asm" -f elf -o "Binaries/kernel_entry.o"

i386-elf-gcc -ffreestanding -m32 -g -IInclude -c "Src/C/kernel.cpp" -o "Binaries/kernel.o"
i386-elf-gcc -ffreestanding -m32 -g -IInclude -c "Src/C/VGA.cpp" -o "Binaries/VGA.o"
i386-elf-gcc -ffreestanding -m32 -g -IInclude -c "Src/C/Keyboard.cpp" -o "Binaries/Keyboard.o"
i386-elf-gcc -ffreestanding -m32 -g -IInclude -c "Src/C/Util.cpp" -o "Binaries/Util.o"
i386-elf-gcc -ffreestanding -m32 -g -IInclude -c "Src/C/CommandProcessor.cpp" -o "Binaries/CommandProcessor.o"
i386-elf-gcc -ffreestanding -m32 -g -IInclude -c "Src/C/IO.cpp" -o "Binaries/IO.o"
i386-elf-gcc -ffreestanding -m32 -g -IInclude -c "Src/C/Disk.cpp" -o "Binaries/Disk.o"

i386-elf-gcc -ffreestanding -m32 -g -IInclude -c "Src/C/testSector.cpp" -o "Binaries/testSector.o"

nasm "Src/ASM/zeroes.asm" -f bin -o "Binaries/zeroes.bin"

i386-elf-ld -o "Binaries/full_kernel.bin" -Ttext 0x10000 "Binaries/kernel_entry.o" "Binaries/kernel.o" "Binaries/VGA.o" "Binaries/IO.o" "Binaries/Keyboard.o" "Binaries/Disk.o" "Binaries/CommandProcessor.o" "Binaries/Util.o" --oformat binary

i386-elf-ld -o Binaries/testSector.bin -Ttext 0x1000 Binaries/testSector.o Binaries/VGA.o --oformat binary

cat "Binaries/boot.bin" "Binaries/full_kernel.bin" "Binaries/zeroes.bin" > "Binaries/OS.bin"

sh sectorAmmount.sh "Binaries/full_kernel.bin"
sh sectorAmmount.sh "Binaries/OS.bin"

dd if=/dev/zero of=DISK.img bs=1 count=1024
dd if=Binaries/testSector.bin of=DISK.img bs=512 count=1 conv=notrunc

qemu-system-x86_64 -drive format=raw,file="Binaries/OS.bin",index=0,if=floppy, -drive format=raw,file="DISK.img",if=ide,index=0  -m 128M
