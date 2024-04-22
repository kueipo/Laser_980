
#ifndef UI_IMG_MAP_H_
#define UI_IMG_MAP_H_
#ifdef __cplusplus
extern "C" {
#endif

/* H == HOVER */

#define FACTORY_APP		0

/* ------------------------------- */
#define APP_BACK        "bac"
#if FACTORY_APP
#define APP_ADDR	    (0)
#else
#define APP_ADDR	        (8 * 1024 * 1024)       // customize
#endif /* FACTORY_APP */
#define APP_SIZE	        (44 * 1024)             // customize
#define PART_00             APP_BACK
#define PART_00_ADDR        APP_ADDR
#define PART_00_SIZE        APP_SIZE
/* ------------------------------- */
#define IMG_PAUSE           "0_0"               // customize
#define IMG_PAUSE_ADDR	    PART_00_ADDR + PART_00_SIZE
#define IMG_PAUSE_SIZE	    (116 * 1024)        // customize
#define PART_01             IMG_PAUSE
#define PART_01_ADDR        IMG_PAUSE_ADDR
#define PART_01_SIZE        IMG_PAUSE_SIZE
/* ------------------------------- */
#define IMG_START           "0_1"               // customize
#define IMG_START_ADDR	    PART_01_ADDR + PART_01_SIZE
#define IMG_START_SIZE	    (116 * 1024)        // customize
#define PART_02             IMG_START
#define PART_02_ADDR        IMG_START_ADDR
#define PART_02_SIZE        IMG_START_SIZE
/* ------------------------------- */
#define IMG_PAUSE_ICO       "0_2"               // customize
#define IMG_PAUSE_ICO_ADDR	PART_02_ADDR + PART_02_SIZE
#define IMG_PAUSE_ICO_SIZE	(24 * 1024)        // customize
#define PART_03             IMG_PAUSE_ICO
#define PART_03_ADDR        IMG_PAUSE_ICO_ADDR
#define PART_03_SIZE        IMG_PAUSE_ICO_SIZE
/* ------------------------------- */
#define IMG_START_ICO        "0_3"              // customize
#define IMG_START_ICO_ADDR	 PART_03_ADDR + PART_03_SIZE
#define IMG_START_ICO_SIZE	 (24 * 1024)        // customize
#define PART_04              IMG_START_ICO
#define PART_04_ADDR         IMG_START_ICO_ADDR
#define PART_04_SIZE         IMG_START_ICO_SIZE
/* ------------------------------- */
#define IMG_LEVEL           "1_0"                // customize
#define IMG_LEVEL_ADDR      PART_04_ADDR + PART_04_SIZE
#define IMG_LEVEL_SIZE      (116 * 1024)          // customize
#define PART_05             IMG_LEVEL
#define PART_05_ADDR        IMG_LEVEL_ADDR
#define PART_05_SIZE        IMG_LEVEL_SIZE
/* ------------------------------- */

#ifdef __cplusplus
}
#endif
#endif /* UI_IMG_MAP_H_ */
