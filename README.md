# Description
    All projects related to STM32F407 uC, include programming using HAL and register programming.

# Software
    - STM32CubeIDE
    - Hercules
    
# Hardware
    - Board STM32F407
    - CP2102 USB to TTL UART Serial Converter Module

# Preferences
    - Set up firmware repo
        + Window -> Preferences 
        + STM32Cube -> Firmware Updater -> Firmware installation repository

# Create project
    - File -> New -> STM32 Project
    - MCU/MPU Selector -> Enter name of MCU to field next to "Commercial Part Number", then choose one of listed MCUs, click Next
    - Enter Project Name, choose Targeted Project Type:
        + STM32Cube: create project using HAL
        + empty: create project using register 
            + Right click to project, choose Properties
            + C/C++ Build -> Settings -> Tool Settings -> MCU GCC Compiler -> Include paths -> Add ..
                "${workspace_loc:/Led_HAL/Drivers/CMSIS/Device/ST/STM32F4xx/Include}"
                "${workspace_loc:/Led_HAL/Drivers/CMSIS/Device/ST/STM32F4xx/Include}"

# Debug with SWV
    - Run -> Debug Configurations... 
        + In tab Debugger -> Enable Serial Wire Viewer (SWV) -> Debug
    - Window -> Show View -> SWV -> SWV ITM Data Console
        + Configure trace -> Tick to ITM Stimulus port 0 -> OK
        + Start trace
    - Resume debugging (F8)
