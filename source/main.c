#include "common.h"
#include "draw.h"
#include "fs.h"
#include "menu.h"
#include "i2c.h"
#include "decryptor/game.h"
#include "decryptor/nand.h"
#include "decryptor/nandfat.h"
#include "decryptor/titlekey.h"

#define SUBMENU_START 1


MenuInfo menu[] =
{
    {
        "XORpad Generator Options", 1,
        {
            { "Health&Safety Dump",           &DumpHealthAndSafety,   0 }
        }
    },
    {
        NULL, 0, {}, // empty menu to signal end
    }
};


void Reboot()
{
    i2cWriteRegister(I2C_DEV_MCU, 0x20, 1 << 2);
    while(true);
}


void PowerOff()
{
    i2cWriteRegister(I2C_DEV_MCU, 0x20, 1 << 0);
    while (true);
}


int main()
{
    ClearScreenFull(true, true);
    InitFS();

    //u32 menu_exit = ProcessMenu(menu, SUBMENU_START);
    DumpHealthAndSafety(0);
    
    DeinitFS();
    PowerOff();
    return 0;
}
