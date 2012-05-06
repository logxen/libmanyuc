/* Adapted for CortexM3 LPC1768, originally based on LPC21xx and LPC22xx User 
 * Manual UM10144, pg. 15. */

OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_startup)

MEMORY
{
	rom (rx)  : ORIGIN = 0x00000000, LENGTH = 512K
	ram (rwx) : ORIGIN = 0x10000000, LENGTH =  32K
}

/* Define the top our stack at the end of SRAM */
_end_stack = 0x10008000;

EXTERN(__interrupt_vector_table);

SECTIONS
{
	.text :
	{
		/* Insert the interrupt vector table first */
		__interrupt_vector_table = .;
		*(.interrupt_vector_table)
		/* Startup assembly */
		*(.startup)

		/* Rest of the code (C) */
		*(.text)
		*(.text.*)
		*(.glue_7)
		*(.glue_7t)
		*(.vfp11_veneer)
		*(.ARM.extab* .gnu.linkonce.armextab.*)
		*(.rodata)
		*(.rodata.*)
		. = ALIGN(8);
		_end_text = .;
		_start_datai = .;
	} >rom

	.data :
	{
		_start_data = .;
		*(vtable)
		*(.data)
		*(.data.*)
		. = ALIGN (8);
		_end_data = .;
	} >ram AT >rom

    .data_init : 
    {
        _end_datai = .;
    } >rom

    __exidx_start = .;
    .ARM.exidx : 
	{ 
		*(.ARM.exidx* .gnu.linkonce.armexidx.*) 
	} > rom
    __exidx_end = .;

	.bss :
	{
		_start_bss = .;
		*(.bss)
		*(COMMON)
	} >ram 

	. = ALIGN(4);
	_end_bss = .;

	. = ALIGN(256);

    /* Stack can grow down to here, right after data and bss sections in 
     * SRAM */
    _start_heap = .;

    PROVIDE( __cs3_heap_start = _start_heap);

	/* Linker wants .eh_frame section defined because of gcc 4.4.X bug,
	 * just discard it here. */
	/DISCARD/ :
	{
		*(.eh_*)
	}
}

_end = .;
PROVIDE(end = .);

