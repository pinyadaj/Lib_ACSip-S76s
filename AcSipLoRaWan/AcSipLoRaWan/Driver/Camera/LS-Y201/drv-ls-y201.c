//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO
//; File Name	 : drv-ls-y201.c
//; Programmer   : Nopparat Ninsamran
//; Email@   	 : nopparat@transcodeglobal.com
//; Objective	 : camera driver for LS-Y201
//; Create(dd/mm/yy) : 12/10/2016
//; [Revision and Description]
//; Rev1.0 - 12/10/2016: Create Library by n.noparat

//;OoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoOoO

//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
//<>
//<> Section 1. Include File
//<>
//<><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><><>
/*  1.1. Standard Library <><><><><><><><><><><><><><><><><><><><><><><><><> */

/*  1.2. Third-Party Library <><><><><><><><><><><><><><><><><><><><><><><>*/

/*  1.3. User Library <><><><><><><><><><><><><><><><><><><><><><><><><><><>*/
#include "drv-ls-y201.h"


// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
//
// Section 2. Public Variable Declare
//
// / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / / /
/* 2.1. Pointer to Function \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 2.2. Pointer to Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 2.3. Memory mapping and ISR Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 2.4. General Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */

/* 2.5. TABLE Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */


// \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
//
// Section 3. Private Variable Declare
//
// \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/
/* 3.1. Pointer to Function \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 3.2. Pointer to Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 3.3. Memory mapping and ISR Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */

/* 3.4. General Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/ */


/* 3.5. TABLE Variable \/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ */


//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
//#
//# Section 4. Private struct and enum Declare
//#
//# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
/* 4.1. enum Declare # # # # # # # # # # # # # # # # # # # # # # # # # # # */

/* 4.2. struct Declare # # # # # # # # # # # # # # # # # # # # # # # # # # */

/* 4.3. function pointer Declare # # # # # # # # # # # # # # # # # # # # # */

//+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + 
//+
//+ Section 5. Private Function Prototype
//+
//+ + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + + 
/* 5.1 general function Prototype* * * * * * * * * * * * * * * * * * * * * * * * */

/* 5.2. user library function Prototype* * * * * * * * * * * * * * * * * * * * * */
int16_t xwrite_camera_ls_y201 (int16_t file_desc, uint8_t *buf_ptr, uint16_t buf_len, uint32_t timout);
int16_t xread_camera_ls_y201 (int16_t file_desc, uint8_t *buf_ptr, uint16_t buf_len, uint32_t timout);

/* 5.3. Helper function Prototype* * * * * * * * * * * * * * * * * * * * * * * * */


//@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ 
//@
//@ Section 6. Interrupt Service Routine
//@
//@ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ @ 


//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
//*
//* Section 7. Public Function Implement
//*
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
/* 7.1 general function * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* 7.2. user library function * * * * * * * * * * * * * * * * * * * * * * * * */

int16_t xwrite_camera_ls_y201 (int16_t file_desc, uint8_t *buf_ptr, uint16_t buf_len, uint32_t timout) {
uint8_t i_cnt;

	/* Send each character in the string, one at a time. */
    for (i_cnt = 0; i_cnt < buf_len; i_cnt++){
        os_putc_uart5 (buf_ptr[i_cnt], timout );      
    }
    
    return (i_cnt);
}

int16_t xread_camera_ls_y201 (int16_t file_desc, uint8_t *buf_ptr, uint16_t buf_len, uint32_t timout) {
uint8_t i_cnt;
int16_t ret;

    for (i_cnt = 0; i_cnt < buf_len; i_cnt++)  {  
          ret = os_getc_uart5((signed char *) buf_ptr++, timout);
          if (ret == pdFALSE) break;
    }

    return (i_cnt);
}

//Send Reset command
int16_t reset_camera_ls_y201 (void) {
uint8_t cmd[128]={0x56, 0x00, 0x26, 0x00};
uint16_t tmp_cnt = 0;  
    if (xwrite_camera_ls_y201 (0, &cmd[0], 4, serNO_BLOCK)) {
        while (xread_camera_ls_y201 (0, &cmd[0], 128, 4000)) {
             for (tmp_cnt = 0; tmp_cnt < 128; tmp_cnt++)  { 
                if ((cmd[tmp_cnt] == 0x0A) && (cmd[tmp_cnt - 1] == 0x0D) && 
                    (cmd[tmp_cnt - 2] == 0x64) && (cmd[tmp_cnt - 3] == 0x6E) &&
                    (cmd[tmp_cnt - 4] == 0x65) ) 
                {
               //     xputs_uart2 ("CAM: End Init\n\r");
                    return 1;
                }
              }
        }
      
        return -1;
    }
    return 0;    
}
 
//Send take picture command
int16_t take_photo_camera_ls_y201 (void){
uint8_t cmd[16]={0x56, 0x00, 0x36, 0x01, 0x00};
uint16_t tmp_cnt = 0;  
    if (xwrite_camera_ls_y201 (0, &cmd[0], 5, serNO_BLOCK)) {
        while (xread_camera_ls_y201 (0, &cmd[0], 16, 100)) {
             for (tmp_cnt = 0; tmp_cnt < 16; tmp_cnt++)  { 
                if ((cmd[tmp_cnt] == 0x00) && (cmd[tmp_cnt - 1] == 0x00) && 
                    (cmd[tmp_cnt - 2] == 0x36) && (cmd[tmp_cnt - 3] == 0x00) &&
                    (cmd[tmp_cnt - 4] == 0x76) ) 
                {
               //     xputs_uart2 ("CAM: Take Picture\n\r");
                    return 1;
                }
              }
        }
      
        return -1;
    }
    return 0; 
}
 

int16_t image_size_camera_ls_y201 (void){
uint8_t cmd[5]={0x56, 0x00, 0x34, 0x01, 0x00};
uint16_t tmp_cnt = 0;  
    if (xwrite_camera_ls_y201 (0, &cmd[0], 5, serNO_BLOCK)) {
        while (xread_camera_ls_y201 (0, &cmd[0], 16, 100)) {
             for (tmp_cnt = 0; tmp_cnt < 16; tmp_cnt++)  { 
                if ((cmd[tmp_cnt] == 0x04) && (cmd[tmp_cnt - 1] == 0x00) && 
                    (cmd[tmp_cnt - 2] == 0x34) && (cmd[tmp_cnt - 3] == 0x00) &&
                    (cmd[tmp_cnt - 4] == 0x76) ) 
                {
              //      xputs_uart2 ("CAM: Image Size \n\r");
                    return 1;
                }
              }
        }
      
        return -1;
    }
    return 0; 
}

//Read data
cam_data_t* read_data_camera_ls_y201 (cam_data_t *cam_data_ptr) {
uint8_t cmd[16]={0x56, 0x00, 0x32, 0x0C, 0x00, 0x0A, 0x00, 0x00, 0xFF, 0xFF, 0x00, 0x00, 0x00,0x80, 0x00, 0x0A };  
uint16_t buf_cnt = 0;
uint16_t data_cnt = 0;
int16_t tmp_len = 0;
  
  if (cam_data_ptr->cam_len < 16 || cam_data_ptr == NULL) {
    return NULL;
  }
  
  cmd[8] = (uint8_t)(cam_data_ptr->cam_addr >> 8);
  cmd[9] = (uint8_t)cam_data_ptr->cam_addr;

  //cmd[12] = (uint8_t)(cam_data_ptr->cam_len>> 8);
 // cmd[13] = (uint8_t)cam_data_ptr->cam_len;
 
    if (xwrite_camera_ls_y201 (0, &cmd[0], 16, serNO_BLOCK)) {
      
        tmp_len = xread_camera_ls_y201 (0, cam_data_ptr->cam_buf_ptr, 138, 50);

        for (buf_cnt = 0; buf_cnt < tmp_len; buf_cnt++)  { 
            if ((cam_data_ptr->cam_buf_ptr[buf_cnt] == 0x00) && 
                (cam_data_ptr->cam_buf_ptr[buf_cnt - 1] == 0x00) && 
                (cam_data_ptr->cam_buf_ptr[buf_cnt - 2] == 0x32) && 
                (cam_data_ptr->cam_buf_ptr[buf_cnt - 3] == 0x00) &&
                (cam_data_ptr->cam_buf_ptr[buf_cnt - 4] == 0x76) ) 
            {
             
                for (data_cnt = 0; data_cnt < 128 ; data_cnt++){ 
                      if ((cam_data_ptr->cam_buf_ptr[buf_cnt + data_cnt] == 0xD9) && (cam_data_ptr->cam_buf_ptr[buf_cnt + data_cnt - 1] == 0xFF)) {
                          cam_data_ptr->cam_status = JPEG_LAST;
                      //    data_cnt;
                          break;
                      }
                      else if ((cam_data_ptr->cam_buf_ptr[buf_cnt + data_cnt + 1] == 0xFF) && (cam_data_ptr->cam_buf_ptr[buf_cnt + data_cnt + 2] == 0xD8)) {
                          cam_data_ptr->cam_status = JPEG_FIRST;
                          data_cnt = tmp_len - 10;
                          break;
                      }
                      else {
                          cam_data_ptr->cam_status = JPEG_CONTI;
                      }
                }
                
                cam_data_ptr->cam_buf_ptr = &cam_data_ptr->cam_buf_ptr[buf_cnt + 1];
                cam_data_ptr->cam_len = data_cnt; 
                
                return cam_data_ptr;
            }
        }
        return NULL;
    }
    
    return NULL;
}
 
int16_t stop_take_photo_camera_ls_y201 (void) {
uint8_t cmd[5]={0x56, 0x00, 0x36, 0x01, 0x03};
uint16_t tmp_cnt = 0;  
    if (xwrite_camera_ls_y201 (0, &cmd[0], 5, serNO_BLOCK)) {
        while (xread_camera_ls_y201 (0, &cmd[0], 5, 100)) {
             for (tmp_cnt = 0; tmp_cnt < 5; tmp_cnt++)  { 
                if ((cmd[tmp_cnt] == 0x00) && (cmd[tmp_cnt - 1] == 0x00) && 
                    (cmd[tmp_cnt - 2] == 0x36) && (cmd[tmp_cnt - 3] == 0x00) &&
                    (cmd[tmp_cnt - 4] == 0x76) ) 
                {
              //      xputs_uart2 ("CAM: Image Size \n\r");
                    return 1;
                }
              }
        }
      
        return -1;
    }
    return 0; 
}

int16_t baudrate_camera_ls_y201 (uint32_t baud) {
uint8_t cmd[7]={0x56, 0x00, 0x24, 0x03, 0x01, 0xAE, 0xC8};
uint16_t tmp_cnt = 0;  

    switch (baud) {
        case 9600: 
          cmd[5] = 0xAE;
          cmd[6] = 0xC8;
          break;
        case 19200: 
          cmd[5] = 0x56;
          cmd[6] = 0xE4;
          break;
        case 38400: 
          cmd[5] = 0x2A;
          cmd[6] = 0xF2;
          break;
        case 57600: 
          cmd[5] = 0x1C;
          cmd[6] = 0x4C;
          break;
        case 115200: 
          cmd[5] = 0x0D;
          cmd[6] = 0xA6;
          break;  
        default: 
          cmd[5] = 0x2A;
          cmd[6] = 0xF2;
          break;  
    }


    if (xwrite_camera_ls_y201 (0, &cmd[0], 7, serNO_BLOCK)) {
        while (xread_camera_ls_y201 (0, &cmd[0], 5, 100)) {
             for (tmp_cnt = 0; tmp_cnt < 5; tmp_cnt++)  { 
                if ((cmd[tmp_cnt] == 0x00) && (cmd[tmp_cnt - 1] == 0x00) && 
                    (cmd[tmp_cnt - 2] == 0x24) && (cmd[tmp_cnt - 3] == 0x00) &&
                    (cmd[tmp_cnt - 4] == 0x76) ) 
                {
              //      xputs_uart2 ("CAM: Image Size \n\r");
                    return 1;
                }
              }
        }
      
        return -1;
    }
    return 0; 
}
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
//*
//* Section 8. Private Function Implement
//*
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * 
/* 8.1 general function * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/* 8.2. user library function * * * * * * * * * * * * * * * * * * * * * * * * */

/* 8.3. Helper function * * * * * * * * * * * * * * * * * * * * * * * * */


//------------------------------------------------------------------------------
//- END of File.
//------------------------------------------------------------------------------
