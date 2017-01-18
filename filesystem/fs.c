#include "fs.h"


#define ATA_MASTER_BUS 0x1F0
#define ATA_SLAVE_BUS 0x170

void select_drive(char bus, char i)
{
	if(bus == ATA_PRIMARY)
		if(i == ATA_MASTER)
			outb(ATA_PRIMARY_IO + ATA_REG_HDDEVSEL, 0xA0);
		else outb(ATA_PRIMARY_IO + ATA_REG_HDDEVSEL, 0xB0);
	else
		if(i == ATA_MASTER)
			outb(ATA_SECONDARY_IO + ATA_REG_HDDEVSEL, 0xA0);
		else outb(ATA_SECONDARY_IO + ATA_REG_HDDEVSEL, 0xB0);
}
