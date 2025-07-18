# Hematite-Project
<!-- ## Overview -->
This is a small ThreadX exercise. The application will run threads to do multiple interfaces and use some of the ThreadX native packages.

A TFT display is used to show the current status of the threads, including each uptime, status, and a dummy data. All threads communicates via queues and a simple semaphore is used to trigger the USB thread.

![img](/resources/app_running.jpg)
## Hardware
- [WeAct STM32H5 Core Board](https://github.com/WeActStudio/WeActStudio.STM32H5_64Pin_CoreBoard)
- ST7789v SPI TFT Display
## Dependencies
- [Floyd's ST7789 driver](https://github.com/Floyd-Fish/ST7789-STM32)
## Application Definition

```mermaid
stateDiagram-v2
    state fork_state <<fork>>
        [*] --> SchedulerStart
    SchedulerStart --> fork_state
    

    fork_state --> DisplayThread
    state DisplayThread {
        [*] --> initSPI
        initSPI --> initDisplay
        initDisplay --> setStaticBackground
        setStaticBackground --> readQueueMessage
        readQueueMessage --> updateMonitorValues
        updateMonitorValues --> readQueueMessage
    }

    fork_state --> USBThread
    state USBThread {
        [*] --> getTicks
        getTicks --> waitForSemaphore
        waitForSemaphore --> printCounterValue
        printCounterValue --> getRunTime
        getRunTime --> sendUSBXThreadMessage
        sendUSBXThreadMessage --> getTicks
    }

    fork_state --> FileThread
    state FileThread {
        [*] --> initSDIO
        initSDIO --> formatSD
        formatSD --> openFile
        openFile --> writeString
        writeString --> closeFile
        closeFile --> [*]

    }

    fork_state --> BlinkyThread
    state BlinkyThread {
        [*] --> getStartTime
        getStartTime --> toggleGPIO
        toggleGPIO --> getCurrentTime
        getCurrentTime --> sendBlikyThreadMessage
        sendBlikyThreadMessage --> putSemaphore
        putSemaphore --> delay
        delay --> toggleGPIO


    }
```

##  
