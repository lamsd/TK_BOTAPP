# TK-BOT Library v0.0.1

Arduino Library for TK-BOT Electronic Modules

# Copyright notice

In TK-BOT's library, some of the modules are derived from other open source projects, and also part of some code is inspired by the algorithms of other individuals or organizations. We will retain the copyright of the original open source code.

As an open source library, we respect all contributors to the open source community and thank you very much for everyone's supervision.

If you have a discussion about licensing issues, please contact me (myan@makeblock.com -- Mark Yan)

### How to use:

1. Download the source from the git https://codeload.github.com/Makeblock-official/Makeblock-Libraries/zip/master

2. In the Arduino IDE: "Sketch-> Include Library-> Add .ZIP Library-> select the downloaded file-> Open"

3. Click "File-> Examples". Here are some test programs in "TK-BOT->"

4. Depending on the type of board you're using, you need to modify the header file to match.

   For example, if you're using a mCore. You should change `#include <TKOrion.h>` to `#include <TKMCore.h>`
   Corresponding boards and there header file are:

   TK-BOT   <-------->  TKOrion.h
  
   
### Revision of history:

|Author        |       Time      |   Version    |    Descr              |
|:--------     |      :-----:    |   :----:     |    :-----             |
|Makeblock     |     2015/07/24  |   3.0.0      |    Created a library. |
|Huynh Lam     |     2020/19/10  |   0.0.1      |    Edit library follow TK-BOT.|
|Pham Duc Minh |     2020/19/10  |   0.0.1      |    Fix error for TK_BOT system.|

### Learn more from TITKUL official website:https://titkul.com/