

#include <cellstatus.h>
#include <sys/prx.h>
#include "Include/message_dialog.h"
#include "Include/cell_sys.h"

#include "Include/trace.h"

SYS_MODULE_INFO( SouthPark_TSOT_IPP, 0, 1, 1);
SYS_MODULE_START( _SouthPark_TSOT_IPP_prx_entry );

SYS_LIB_DECLARE_WITH_STUB( LIBNAME, SYS_LIB_AUTO_EXPORT, STUBNAME );
SYS_LIB_EXPORT( _SouthPark_TSOT_IPP_export_function, LIBNAME );

// An exported function is needed to generate the project's PRX stub export library
extern "C" int _SouthPark_TSOT_IPP_export_function(void)
{
    return CELL_OK;
}

extern "C" int _SouthPark_TSOT_IPP_prx_entry(void)
{

        
    debug::create();
    debug::out::write("South Park: The Stick Of Truth\n");

    return SYS_PRX_RESIDENT;
}
