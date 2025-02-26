# GCP125

- 可穿戴设备生物医学开发平台
    - 硬件 - 单通道蓝牙主板 GCP125 / 生物传感器板 （ECG、EMG、PPG、EEG）
    - 固件 - 使用 Arduino IDE 开发或恢复 GCP125蓝牙主板
    - 软件 - 适用于 GCP125 的 Android 应用程序

# **固件**

本文档包括以下内容：

1. **[对于用户]** 使用**出厂设置**轻松获取主板 和传感器板的数据。
2. **[对于开发人员]**您需要了解的有关 GCP125 作为微控制器的基本信息。
    
    **A. GCP125 描述**
    
    **B. 使用 GCP125 Arduino IDE 进行开发**
    
3. 常见问题 **（FAQ）**

# 1. [用户端] GCP125出厂设置和使用

- **A. GCP125有 1 个通道用于连接传感器板。**

![https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image1.png](https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image1.png)

- **B. 快速启动步骤：**
    - 选择传感器板和软件
        - 传感器板：ECG、EEG、EMG、PPG
        - 软件 - 适用于 GCP125 的Android 应用程序
    - GCP125在其上组装传感器板。
    - 连接GCP125和APP，然后获得生物信号！
- **C. 一个启动示例：**
    - 选择EEG子板作为传感器板，然后选择Android应用程序作为软件
    
    ![https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image2.png](https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image2.png)
    
    - 将传感器板插入GCP125母板，然后将电极线的3.5mm头插入传感板，电极人体太阳穴两端
    
    ![https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image3.png](https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image3.png)
    
    - Android 应用程序：扫描、连接，然后转动眼球开始显示生物信号
    
    ![https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image4.png](https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image4.png)
    
    ![https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image5.png](https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image5.png)
    
- **D. 其他不同情况的固件：**
    - 用于**无线**通信
        - 固件：
            - GCP125 Official Firmware：GCP125出厂固件
            - GCP125 ECG_BT：GCP125母板上LED会随心跳脉冲闪烁
            - GCP125 PPG_BT：GCP125母板上LED会随心跳脉冲闪烁
            - GCP125 EEG_BT：GCP125母板上LED会随眼睛左右看控制其亮灭
            - GCP125 EMG_BT：GCP125母板上LED会肌肉收缩点亮
        - 软件：安卓（BLE102）
- **E.如何将出厂设置固件更改为其他固件？**
    - **Arduino BSP 方法**
        - **a**. 将GCP125.rar放到C:\Users\admin\AppData\Local\Arduino15\packages目录下解压
        - **b**. 启动 Arduino IDE
        - **c**. 选择工具 > 开发板 > GCP125 Board（nRF52 Series）> GCP125 nRF52840
            
            ![https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image6.png](https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image6.png)
            
        - **d**. 选择工具 > 编程器 > GCP125 Official Firmware
            
            ![https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image7.png](https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image7.png)
            
        - **e**. 选择工具 > 端口 > COMXX (GCP125 nRF52840)
            
            ![https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image8.png](https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image8.png)
            
        - **f**. 选择工具 > 烧录引导程序
        - **g**. 等待大约 5~10 秒，如果跳出以下表扬，则表示**未成功**，请按照以下步骤操作。
            
            ![https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image9.png](https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image9.png)
            
        - **h**. 选择工具 > 端口 > COMYY (GCP125 nRF52840)**（YY 不会等于 XX）**
        - **i**.  选择工具 > 烧录引导程序
        - **j**. 等待大约 10~30 秒，如果显示以下表扬，则表示**成功**。
            
            ![https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image10.png](https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image10.png)
            

# **2. [对于开发人员] GCP125 出厂设置和使用**

**A. GCP125 描述**

- a. 引脚配置
    
    ![image11.png](https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image11.png)
    
- **b.Pin 功能描述**

![image12.png](https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image12.png)

![image13.png](https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image13.png)

![image14.png](https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image14.png)

![image15.png](https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image15.png)

**B. 在 Arduino IDE 上使用 GCP125 进行开发**

- ***a. 环境建立***：将我司提供的GCP125.rar放到C:\Users\admin\AppData\Local\Arduino15\packages目录下解压
    - I. [下载并安装 Arduino IDE](https://www.arduino.cc/en/Main/Software)（最新版）
        - 选择操作系统的版本。
        - 直接按捐赠页面中的**“Just Download”。**
            
            ![image16.png](https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image16.png)
            
    - II. 将GCP125.rar放到C:\Users\admin\AppData\Local\Arduino15\packages目录下解压
    - III. 启动 Arduino IDE
    - IV. 选择 Boards Manager
        - 选择工具 > 开发板 > GCP125 Board（nRF52 Series）> GCP125 nRF52840
        
        ![image17.png](https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image17.png)
        
- **b. 上传并运行您的代码**
    - I. 选择一个示例代码或制作您自己的代码。文件 > 示例 > GCP125 > ECG_BT
    - II. 将 GCP125母板与 PC 连接。（建议：使用 USB 作为电源）
    - III. 选择工具 > 开发板 > GCP125 Board（nRF52 Series）> GCP125 nRF52840
        
        ![image18.png](https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image18.png)
        
    - IV. 选择工具 > 端口 > COMXX (GCP125 nRF52840)
        
        ![image19.png](https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image19.png)
        
    - V. 按 （编译 + 上传），或按 （编译），然后按 （上传））。
        
        ![image20.png](https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image20.png)
        
        ![image21.png](https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image21.png)
        
        ![image22.png](https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image22.png)
        
    - **上传成功 👋 显示 Device programmed （设备已编程）**
        
        ![image23.png](https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image23.png)

        

**附录。如果你遇到了什么麻烦......尝试重新烧录 Bootloader!!!**

方法 1：仅通过 USB 数据线将 GCP125-MDBT50Q板连接到 PC。

方法 2： 通过 J-Link 设备和 USB 数据线将GCP125-MDBT50Q板连接到 PC。（仅限致命错误）

- -------------------------------------------------------------**方法 1**
- I. 选择工具 > 开发板 > GCP125 Board（nRF52 Series）> GCP125 nRF52840
- II. 选择工具 > 端口 > COMXX (GCP125 nRF52840)
- III. 选择工具 > 编程器 > GCP125 Official Firmware
- IV. 选择工具 >烧录引导程序
- V. 等待约 20~30 秒。
- **成功刻录的图**
    
    ![image24.png](https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image24.png)
    

**方法 2**

- I. 要使用 J-Link，用户应在此处安装驱动程序[**。**](https://www.segger.com/downloads/jlink/)
- II. 选择您的操作系统并点击下载。
    
    ![image25.png](https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image25.png)
    
- III. 安装驱动程序。
    
    ![image26.png](https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image26.png)
    
- IV. 将 GCP125-MDBT50Q和 J-link 连接到您的 PC。
    
    ![image27.png](https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image27.png)
    
- V. 启动 Arduino IDE。
- VI. 选择工具 > 端口 > COMZ（J-Link端口）
- VII. 选择工具 > 编程器 > J-Link for GCP125 nRF52
- VIII. 选择工具 >烧录引导程序
- IX. 等待约 20~30 秒。
- **成功刻录的图**
    
    ![image28.png](https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image28.png)
    

# **3. [常见问题 （FAQ）]**

**Q1 -> 如果您对** GCP125**默认固件有问题......**

1. 请确认你的 arduino IDE 在执行GCP125**默认固件 / 应用程序 - 固件设置步骤**中的步骤后，是否有下图所示的注释。
    
    ![image28.png](https://github.com/CKQQQQQQ/GCP125/blob/master/Asset/GCP125/image29.png)
    
2. 请勿移除您的设备并重新执行GCP125 **默认固件/应用程序 - 固件设置步骤**的第 4~5 步。

**Q2 -> 如果您在 Arduino IDE 中工具 > 开发板无法找到GCP125**

1. 请下载最新的 Arduino IDE 版本。
