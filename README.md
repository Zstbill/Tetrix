# Tetrix

基于Qt的俄罗斯方块小游戏，支持存档，单双人游戏

| **设计报告**                                                 |
| ------------------------------------------------------------ |
| 【程序描述】  基于C++、Qt编写的一款俄罗斯方块小游戏，实现任务一到四的全部功能，并且增加双人模式的玩法。  界面简约而丰富，玩家所有需求均可在主界面得到实现。（推荐屏幕分辨率1920*1080）<br /> 【系统设计说明】  <br /><br />（1）**数据结构说明**：  widget.h 主窗口  selectmode.h 选择模式窗口  tetrixwindow.h 游戏界面窗口  tetrixpiece.h 俄罗斯方块类  tetrixboard.h 棋盘类  file.h 存档窗口  rank.h 排行榜窗口  Setting.h 设置窗口  Instruction.h 游戏说明窗口  changebackground.h 更改背景窗口  changebgm.h 更改bgm窗口  changeboard.h 更改棋盘大小窗口  changecolor.h更改颜色与下落速度窗口  changekey.h 更改键位窗口 <br />其中Tetrixwindow.h中包含Tetrixboard.h，用于棋盘的展示。  <br /><br />窗口类均继承于QWidget，Tetrixboard.h继承于QFrame。Tetrixpiece.h 为新建类  每个类都包含析构函数，不存在内存泄漏的现象。   <br /><br />（2）**程序功能说明**:     <br /><br />**各模块功能**：在数据结构说明中有简单介绍。  <br />主界面中“新游戏”按钮可以进行模式选择。分为单人简单，单人极限，双人模式  “设置”按钮可以进行五项设置。键位设置提供恢复默认选项。  “排行榜”按钮可以查看排行榜以及清空排行榜。 <br />“游戏说明”可以查看具体键位以及玩法。  <br />“存档”可以查看目前的所有存档，并从其中之一开始，或复制删除。<br />“退出”按钮即退出游戏。  <br />在进行游戏时，可以暂停，并且可以使用快捷键开始与暂停。<br />单人游戏过程中可以随时存档，并输入存档名字以确定玩家身份，也可以随时载入存档。<br />两种模式的存档分别存储，在不同模式打开存档时会提示。  <br />在游戏结束后，会弹窗提示是否需要参与排行榜，并输入名字。<br />排行榜仅收录单人的两种模式的前五名。  在设置界面，具体操作见演示视频。    <br /> **算法描述**：俄罗斯方块中主要由大量模拟组成，使用到的算法较少。  <br />在排行榜的存储中用到快速排序算法。  <br />计算得分时用到计分算法：在消除一行方块时加10分，当一个方块下落到底时，加1分，若使用下落到底键，则分数再增加方块下落到底的行数÷5的分数。  <br />计算level时的算法：每生成5个方块level+1  level的增加会导致方块下落速度变快。一个level的增加导致方块下落速度增加10%  <br />随机生成方块算法：在一组7个方块中优先生成未出现的方块，当7种方块全部出现一次后，开始新的一轮刷新。     <br /><br />**接口说明**：  <br /><br />棋盘类包含：  void saveGame();保存游戏  void loadGame();加载游戏  void start();开始游戏  void pause();暂停  void scoreChanged(int score);得分改变   void levelChanged(int level);level改变level  void linesRemovedChanged(int numLines);改变消除行数  void paintEvent(QPaintEvent *event)  override;打印方块  void keyPressEvent(QKeyEvent *event)  override;检测键盘输入  void timerEvent(QTimerEvent *event)  override;方块下落与判断游戏结束  TetrixShape &shapeAt(int x, int y) {  return board[(y * BoardWidth) + x]; }返回（x，y）位置的方块种类  void clearBoard();清屏  void dropDown();方块下落到底  void oneLineDown();方块下落一行  void pieceDropped(int dropHeight);判断加分  void removeFullLines();清除一行的方块  void newPiece();生成新的方块  void showNextPiece();展示新方块  bool tryMove(const TetrixPiece  &newPiece, int newX, int newY);判断方块能否移动  void drawSquare(QPainter &painter, int  x, int y, TetrixShape shape,int color);画出方块     <br /><br />方块类包含：  TetrixPiece rotatedLeft() const;方块逆时针旋转  TetrixPiece rotatedRight() const;方块顺时针旋转  void setRandomShape() 得到随机方块     <br /><br />**关键变量说明**：  棋盘类包含：  int Boardwidth，Boardheight;棋盘宽度高度  int timeout;下落时间  bool isStarted;是否开始  bool isPaused;是否暂停  bool isWaitingAfterLine;是否出现下一块  TetrixPiece curPiece;当前方块  TetrixPiece nextPiece;下一个方块  int curX;当前方块x坐标  int curY;当前方块y坐标  int numLinesRemoved;一次消除的行数  int numPiecesDropped;方块下落到底的行数  int score;得分  int level;等级  int if_jixian;是否是极限模式  int color=1;方块颜色预设     方块类包含：  TetrixShape pieceShape;方块种类  int coords[4][2];坐标  int minX() const;方块x轴最大值  int maxX() const; 方块y轴最大值  int minY() const; 方块x轴最小值  int maxY() const; 方块y轴最小值     设置中：在可执行文件目录下有：  key.ini 键位配置保存  color.ini 方块颜色、下落速度、背景保存  rank.ini 极限模式排行榜保存  easyrank.ini 简单模式排行榜保存     <br /><br />【实现环境】  <br />（1）   设计平台要求：  Windows    <br />（2）   运行环境要求：  IDE：Qt Creator（qmake)  <br />             编译器：Qt 5.15.2 MinGW_64_bit |
|                                                              |
| 【设计实现及分析】   <br /><br />问题：  <br />（1）构建游戏底层时遇到方块位置越界的问题，导致游戏无法继续进行。  解决方法：完善判断方块能否移动的函数  <br />（2）双人模式键位问题  解决方法：将键位设置在一个棋盘内。  <br />（3）排行榜数据的存储  解决方法：利用QSettings，存储一个QPair<QString,int>  <br />（4）存档的存储，与读取  解决方法：以顺序文件的方式存储，存储模式、棋盘大小、当前下落方块，已经下落的方块地图。读取时先读取模式进行判断，再修改棋盘参数。  <br />（5）键位设置  解决方法：创建一个QMap<QString,int>保存键位名称以及对应的ascii码值并存储到QSettings中。  程序测试方法：利用Qt Creator中的调试功能。以及自己对于程序的感知。 <br />    <br />【讨论】  目前本人对于程序较为满意，若还有时间可以继续开发更多游戏玩法以及功能。<br />  <br />**程序结构**：于前文中展示，结构较为合理，并且有拓展性，可以较为方便地进行增加功能。  <br />**时空效率**：程序均为模拟，时间效率为O(1)。进行排序时，效率为O(nlogn)。程序的空间占用较少，不存在大数组，可以忽略其对内存的影响。    <br /><br />【系统使用说明】  具体见演示视频 https://www.bilibili.com/video/BV15o4y1g7qg/ |

 