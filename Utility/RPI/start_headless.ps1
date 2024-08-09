
# PowerShell Script to Run QEMU on Windows

# Get the directory of the current script
$scriptDir = Split-Path -Parent $MyInvocation.MyCommand.Definition

# Define paths to the kernel and image files
$kernel = Join-Path -Path $scriptDir -ChildPath "linux-6.6.20-image"
$image = Join-Path -Path $scriptDir -ChildPath "2024-07-04-raspios-bookworm-arm64.img"

# # QEMU System Configuration
# $qemuPath = "qemu-system-aarch64" # QEMU executable path, adjust if needed

# Make sure that QEMU is installed and in the PATH
Write-Output "Make sure that QEMU (64-bit) is installed and in the PATH"

# Check if qemu is 64 bit
$qemuPath = Get-Command qemu-system-aarch64
if ($null -eq $qemuPath) {
    Write-Output "QEMU (64-bit) is not installed or not in the PATH"
    exit
}

# QEMU Arguments
$qemuArgs = @(
    "-machine", "virt", # Set the machine type
    "-cpu", "cortex-a72", # Define the CPU type
    "-smp", "6", # Set the number of CPU cores
    "-m", "4G", # Allocate memory size
    "-kernel", $kernel, # Specify the kernel path
    "-append", "root=/dev/vda2 rootfstype=ext4 rw panic=0 console=ttyAMA0", # Kernel command line
    "-drive", "format=raw,file=$image,if=none,id=hd0,cache=writeback", # Define the drive
    "-device", "virtio-blk,drive=hd0,bootindex=0", # Define the block device
    "-netdev", "user,id=mynet,hostfwd=tcp::2222-:22", # Network device with port forwarding
    "-device", "virtio-net-pci,netdev=mynet", # Network PCI device
    "-display", "none", # Display type
    "-serial", "stdio" # Serial output to standard I/O
)

& $qemuPath @qemuArgs
