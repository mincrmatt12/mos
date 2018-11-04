# MOS Bootloader

Also known as MBoot.

The MOS bootloader is responsible for finding the M-Kernel type partition, loading the kernel and drivers located there and jumping to it.

## M-Kernel FS

Identified with the GPT partition type "162cb3ff-e526-4d8c-854f-f576992ef3d9". Built for housing:

- the kernel image
- its core drivers (fs io, boot media, and terminal io)
- kernel boot parameters

Despite being called a filesystem, there really aren't that many file-like things.
The filesystem starts with a header:

| offset | type | meaning |
| 0x0 | uint32_t | Signature: "MKFS" in ascii |
| 0x4 | uint32_t | Revision: currently 1 |
| 0x8 | uint32_t | Size of boot parameters in bytes |
| 0xc | uint64_t | Size of kernel image |
| 0x14 | uint32_t | Number of driver images |
| 0x18 | uint64_t | Offset to boot parameters |
| 0x20 | uint64_t | Offset to kernel image |
| 0x28 | uint64_t | Offset to driver index |
| 0x30 | uint32_t | crc32 of this header |

offsets are from beginning of fs

Boot parameters are stored as an ascii string with no terminating null.
Kernel image is stored verbatim in its format.
Driver index is a list of the following, with the number of entires in the header.

| offset | type | meaning |
| 0x0 | uint16_t | name length |
| 0x2 | uint64_t | offset from fs start to driver image |
| 0xa | ascii non-null-terminated string | filename |

If required, the filesystem can be emulated as a traditional file based system and shall have the following structure:

- /
  - /kernel - the kernel image
  - /params.txt - kernel parameters
  - /drivers/
    - (driver_name)


