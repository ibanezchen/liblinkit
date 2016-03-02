/**
 * @file os_cli.h
 *
 *  os_cli command
 *
 */

#ifndef __OS_CLI_H__
#define __OS_CLI_H__

#if defined(MTK_MINICLI_ENABLE)

/**
 * @ingroup OS
 * @addtogroup CLI
 * @{
 */


#include <stdint.h>


#ifdef __cplusplus
extern "C" {
#endif

uint8_t os_cli_show_task_info(uint8_t len, char *param[]);
uint8_t os_cli_cpu_utilization(uint8_t len, char *param[]);

#ifdef __cplusplus
}
#endif


/** }@ */

#endif

#endif /* __OS_CLI_H__ */
