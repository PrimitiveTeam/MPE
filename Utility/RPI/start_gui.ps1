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

# Display devices:
# name "ati-vga", bus PCI
# name "bochs-display", bus PCI
# name "cirrus-vga", bus PCI, desc "Cirrus CLGD 54xx VGA"
# name "dm163", desc "DM163"
# name "led", desc "LED"
# name "ramfb", bus System, desc "ram framebuffer standalone device"
# name "secondary-vga", bus PCI
# name "ssd0323", bus SSI
# name "VGA", bus PCI
# name "virtio-gpu-device", bus virtio-bus
# name "virtio-gpu-gl-device", bus virtio-bus
# name "virtio-gpu-gl-pci", bus PCI, alias "virtio-gpu-gl"
# name "virtio-gpu-pci", bus PCI, alias "virtio-gpu"

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
    "-display", "sdl", # Display type
    "-device", "virtio-gpu-pci", # GPU device
    "-device", "usb-ehci", # USB EHCI controller
    "-device", "usb-kbd", # USB keyboard
    "-device", "usb-mouse", # USB mouse
    "-serial", "stdio" # Serial output to standard I/O
)

# Execute QEMU with the specified arguments
& $qemuPath @qemuArgs

# OpenGL Hardware Acceleration:
# CURRENTLY NOT WORKING
# $qemuArgs = @(
#     "-machine", "virt", # Set the machine type
#     "-cpu", "cortex-a72", # Define the CPU type
#     "-smp", "6", # Set the number of CPU cores
#     "-m", "4G", # Allocate memory size
#     "-kernel", $kernel, # Specify the kernel path
#     "-append", "root=/dev/vda2 rootfstype=ext4 rw panic=0 console=ttyAMA0", # Kernel command line
#     "-drive", "format=raw,file=$image,if=none,id=hd0,cache=writeback", # Define the drive
#     "-device", "virtio-blk,drive=hd0,bootindex=0", # Define the block device
#     "-netdev", "user,id=mynet,hostfwd=tcp::2222-:22", # Network device with port forwarding
#     "-device", "virtio-net-pci,netdev=mynet", # Network PCI device
#     "-display", "sdl,gl=on", # Display type
#     "-device", "virtio-gpu-gl-pci", # GPU device
#     "-device", "usb-ehci", # USB EHCI controller
#     "-device", "usb-kbd", # USB keyboard
#     "-device", "usb-mouse", # USB mouse
#     "-serial", "stdio" # Serial output to standard I/O
# )
