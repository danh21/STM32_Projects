# Description
- All projects related to STM32F407 uC, include programming using HAL and register programming.
- In each project, readme.doc describes setup to test project
- Always open 0_base_HAL as base project. Register projects include libraries from this project.
- 0_Library includes driver source of modules (in-progress).
  
### Software
- STM32CubeIDE
- Hercules
    
### Hardware
- Board STM32F407
- CP2102 USB to TTL UART Serial Converter Module
- Variable resistor
- Module I2C PCF8574 + LCD 20x4
- Led
- Resistors

# Setting
### Preferences
- Set up firmware repo
    + Window -> Preferences 
    + STM32Cube -> Firmware Updater -> Firmware installation repository
      ![image](https://github.com/user-attachments/assets/026a6f03-12d7-4c01-9e76-4ff3d6ee0d01)

### Create project
- File -> New -> STM32 Project
- MCU/MPU Selector -> Enter name of MCU to field next to "Commercial Part Number", then choose one of listed MCUs, click Next
  ![image](https://github.com/user-attachments/assets/bf571465-ce13-4dfd-ae7c-abc724761cdd)
- Enter Project Name, choose Targeted Project Type:
    + STM32Cube: create project using HAL
    + empty: create project using register 
        + Right click to project, choose Properties
        + C/C++ Build -> Settings -> Tool Settings -> MCU GCC Compiler -> Include paths -> Add ..
          "${workspace_loc:/Led_HAL/Drivers/CMSIS/Device/ST/STM32F4xx/Include}"
          "${workspace_loc:/Led_HAL/Drivers/CMSIS/Device/ST/STM32F4xx/Include}"
          ![image](https://github.com/user-attachments/assets/20b0c70b-da51-4342-86dc-1522ed1aa7fa)

### Debug with console
- Run -> Debug Configurations... 
- In tab Debugger -> Enable Serial Wire Viewer (SWV) -> Debug
  ![image](https://github.com/user-attachments/assets/4e1f4320-5da8-4d10-8d27-05b4b97cbe59)
- Window -> Show View -> SWV -> SWV ITM Data Console
    + Configure trace -> Tick to ITM Stimulus port 0 -> OK
    + Start trace
    ![image](https://github.com/user-attachments/assets/c2807713-14b1-472d-bc5f-ba9a8174a8db)
- Resume debugging (F8)

### Debug with waveform
- Run -> Debug Configurations... 
- In tab Debugger -> Enable Serial Wire Viewer (SWV) -> Debug
- Window -> Show View -> SWV -> SWV Data Trace Timeline Graph
    + Data Trace -> Comparator -> Enable -> variable
    + Configure trace -> Tick to ITM Stimulus port 0 -> OK
    + Start trace
    ![Screenshot_1](https://github.com/user-attachments/assets/0309d207-d2f0-4763-b5a9-d77349d714c3)
- Resume debugging (F8)
