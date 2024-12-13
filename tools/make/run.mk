run:
	$(info run [release] build)
	@qemu-system-riscv64 -machine virt -cpu rv64 -smp 4 -m 512M -nographic -serial mon:stdio -bios none -kernel build/kernel.img

debug:
	$(info run [debug] build)
	@qemu-system-riscv64 -s -S -machine virt -cpu rv64 -smp 4 -m 512M -nographic -serial mon:stdio -bios none -kernel build/kernel.img