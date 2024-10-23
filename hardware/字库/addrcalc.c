//code 字符指针开始
//从字库中查找出字模
//code 字符串的开始地址,GBK码
//mat  数据存放地址 (size/8+((size%8)?1:0))*(size) bytes大小    
//size:字体大小
void Get_HzMat(unsigned char *code,unsigned char *mat,u8 size)
{            
    unsigned char c1,c2,c3,c4;//汉字内码
    unsigned char i;                      
    unsigned long foffset; 
    unsigned long h=0;
    u8 csize=(size/8+((size%8)?1:0))*(size);//得到字体一个字符对应点阵集所占的字节数     
    c1=*code;
    c2=*(++code);
    c3=*(++code);
    c4=*(++code);
    if(c2==0x7f)
    {               
        for(i=0;i<csize;i++)*mat++=0x00;//填充满格
        return; //结束访问
    }
    if(size==12)
    {    
            if(c1 >= 0xA1 && c1 <= 0xa9 && c2 >= 0xa1) //Section 1
                h = (c1 - 0xA1) * 94 + (c2 - 0xA1);
            else if(c1 >= 0xa8 && c1 <= 0xa9 && c2 < 0xa1) //Section 5
            {
                if(c2 > 0x7f)
                    c2--;
                h = (c1 - 0xa8) * 96 + (c2 - 0x40) + 846;
            }
            if(c1 >= 0xb0 && c1 <= 0xf7 && c2 >= 0xa1) //Section 2
                h = (c1 - 0xB0) * 94 + (c2 - 0xA1) + 1038;
            else if(c1 < 0xa1 && c1 >= 0x81 && c2 >= 0x40 ) //Section 3
            {
                if(c2 > 0x7f)
                    c2--;
                    h=(c1-0x81)*190 + (c2-0x40) + 1038 +6768;
            }
            else if(c1>=0xaa && c2<0xa1) //Section 4
            {
            if(c2>0x7f)
            c2--;
            h=(c1-0xaa)*96 + (c2-0x40) + 1038 +12848;
            }
            foffset=h*24;
            SPI_Flash_Read(mat,foffset+0x093D0E,24);
    }
    
    else    if(size==16)
    {    
                if(c1 <= 0xA1 && c1 >= 0xA0 && c2 >= 0xa1) //Section 1 标点
                    h = (c1 - 0xA1) * 94 + (c2 - 0xA1);
                else if(c1 >= 0xa8 && c1 <= 0xa9 && c2 < 0xa1) //Section 5
                {
                    if(c2 > 0x7f)
                        c2--;
                    h = (c1 - 0xa8) * 96 + (c2 - 0x40) + 846;
                }
                if(c1 >= 0xb0 && c1 <= 0xf7 && c2 >= 0xa1) //Section 2
                    h = (c1 - 0xB0) * 94 + (c2 - 0xA1) + 1038;
                else if(c1 < 0xa1 && c1 >= 0x81 && c2 >= 0x40 ) //Section 3
                {
                    if(c2 > 0x7f)
                        c2--;
                    h = (c1 - 0x81) * 190 + (c2 - 0x40) + 1038 + 6768;
                }
                else if(c1 >= 0xaa && c2 < 0xa1) //Section 4
                {
                    if(c2 > 0x7f)
                        c2--;
                    h = (c1 - 0xaa) * 96 + (c2 - 0x40) + 1038 + 12848;
                }
                else if(c1 == 0x81 && c2 >= 0x39) //四字节区 1
                {
                    h = 1038 + 21008 + (c3 - 0xEE) * 10 + c4 - 0x39;
                }
                else if(c1 == 0x82) //四字节区 2
                {
                    h = 1038 + 21008 + 161 + (c2 - 0x30) * 1260 + (c3 - 0x81) * 10 + c4 - 0x30;
                }
            foffset=h*32;
            SPI_Flash_Read(mat,foffset+0x114FDE,32);
    }
    if(size==24)
    {    
                if(c1 >= 0xA1 && c1 <= 0xAB && c2 >= 0xa1) //Section 1
                    h = (c1 - 0xA1) * 94 + (c2 - 0xA1);
                else if(c1 >= 0xa8 && c1 <= 0xa9 && c2 < 0xa1) //Section 5
                {
                    if(c2 > 0x7f)
                        c2--;
                    h = (c1 - 0xa8) * 96 + (c2 - 0x40) + 846;
                }
                if(c1 >= 0xb0 && c1 <= 0xf7 && c2 >= 0xa1) //Section 2
                    h = (c1 - 0xB0) * 94 + (c2 - 0xA1) + 1038;
                else if(c1 < 0xa1 && c1 >= 0x81 && c2 >= 0x40) //Section 3
                {
                    if(c2 > 0x7f)
                        c2--;
                    h = (c1 - 0x81) * 190 + (c2 - 0x40) + 1038 + 6768;
                }
                else if(c1 >= 0xaa && c2 < 0xa1) //Section 4
                {
                    if(c2 > 0x7f)
                        c2--;
                    h = (c1 - 0xaa) * 96 + (c2 - 0x40) + 1038 + 12848;
                }
                else if(c1 == 0x81 && c2 >= 0x39) //四字节区  1
                {
                    h = 1038 + 21008 + (c3 - 0xEE) * 10 + c4 - 0x39;
                }
                else if(c1 == 0x82) //四字节区  2
                {
                    h = 1038 + 21008 + 161 + (c2 - 0x30) * 1260 + (c3 - 0x81) * 10 + c4 - 0x30;
                }
                foffset=h*72;
                SPI_Flash_Read(mat,foffset+0x1F43DE,72);
    }                                                                   
}  
//显示一个指定大小的汉字
//x,y :汉字的坐标
//font:汉字GBK码
//size:字体大小
//mode:0,正常显示,1,叠加显示       
void Show_Font(u16 x,u16 y,u8 *font,u8 size,u8 mode)
{
    u8 temp,t,t1;
    u16 x0=x;
    u8 dzk[72];   
    u8 csize=(size/8+((size%8)?1:0))*(size);//得到字体一个字符对应点阵集所占的字节数     
    if(size!=12&&size!=16&&size!=24)return;    //不支持的size
    Get_HzMat(font,dzk,size);    //得到相应大小的点阵数据 
    for(t=0;t<csize;t++)
    {                                                      
        temp=dzk[t];            //得到点阵数据                          
        for(t1=0;t1<8;t1++)
        {
            if(temp&0x80)LCD_Fast_DrawPoint(x,y,POINT_COLOR);
            else if(mode==0)LCD_Fast_DrawPoint(x,y,BACK_COLOR); 
            temp<<=1;
            x++;
            if((x-x0)==size)
            {
                x=x0;
                y++;
                break;
            }
        }       
    }  
}





//在指定位置显示一个字符 从字库中取
//x,y:起始坐标
//num:要显示的字符:" "--->"~"
//size:字体大小 12/16/24
//mode:叠加方式(1)还是非叠加方式(0)
void LCD_ShowChar_ZK(u16 x,u16 y,u8 num,u8 size,u8 mode)
{                                
    u8 temp,t1,t;
    u16 x0=x;
    u8 cache[48];
    u8 csize=(size/8+((size%8)?1:0))*(size/2);        //得到字体一个字符对应点阵集所占的字节数    24号字最大用48
     num=num-0x20;//得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库）
    
        if(size==12)SPI_Flash_Read(cache,num*12+0x080900,12);         //调用1206字体
        else if(size==16)SPI_Flash_Read(cache,num*16+0x080D80,16);    //调用1608字体
        else if(size==24){SPI_Flash_Read(cache,num*48+0x081B80,48);csize=48;}    //调用2412字体
        else return;                                //没有的字库    
    
    for(t=0;t<csize;t++)
    {   
        temp=cache[t];
        for(t1=0;t1<8;t1++)
        {                
            if(temp&0x80)LCD_Fast_DrawPoint(x,y,POINT_COLOR);
            else if(mode==0)LCD_Fast_DrawPoint(x,y,BACK_COLOR);
            temp<<=1;
            x++;
            //if(x>=lcddev.width)return;    //超区域了            
            if((x-x0)==size/2)
            {
                x=x0;
                y++;
                //if(y>=lcddev.height)return;        //超区域了
                break;
            }
        }       
    }                            
}   
//在指定位置开始显示一个字符串        
//支持自动换行
//(x,y):起始坐标
//width,height:区域
//str  :字符串
//size :字体大小
//mode:0,非叠加方式;1,叠加方式                      
void Show_Str(u16 x,u16 y,u16 width,u16 height,u8*str,u8 size,u8 mode)
{                    
    u16 x0=x;
    u16 y0=y;                                    
    u8 bHz=0;     //字符或者中文                                                      
    while(*str!=0)//数据未结束
    { 
        if(!bHz)
        {
            if(*str>0x80)bHz=1;//中文 
            else              //字符
            {      
                if(x>(x0+width-size/2))//换行
                {                   
                    y+=size;
                    x=x0;       
                }                                
                if(y>(y0+height-size))break;//越界返回      
                if(*str==13)//换行符号
                {         
                    y+=size;
                    x=x0;
                    str++; 
                }  
                else LCD_ShowChar_ZK(x,y,*str,size,mode);//有效部分写入     外部字库
                        // else LCD_ShowChar(x,y,*str,size,mode);//有效部分写入  内部字库
                str++; 
                x+=size/2; //字符,为全字的一半 
            }
        }else//中文 
        {     
                    bHz=0;//有汉字库    
                    if(x>(x0+width-size))//换行
                    {        
                        y+=size;
                        x=x0;          
                    }
            if(y>(y0+height-size))break;//越界返回                               
            Show_Font(x,y,str,size,mode); //显示这个汉字,空心显示 
            str+=2; 
            x+=size;//下一个汉字偏移        
        }                         
    }   
}
