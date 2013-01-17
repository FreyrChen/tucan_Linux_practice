package com.example.airsync; 

/* import相关class */
import java.util.ArrayList;
import java.util.List;
import org.xml.sax.Attributes; 
import org.xml.sax.SAXException; 
import org.xml.sax.helpers.DefaultHandler; 
/*
 * 将xml文件中的照片信息解析出来
 */
public class PhotoHandler extends DefaultHandler
{
  private List<String> list;
  /*返回相片信息 */
  public List<String> getPhotos()
  { 
    return list;
  }

  /* XML文件开始解析时调用此method */
  @Override 
  public void startDocument() throws SAXException
  { 
    list = new ArrayList<String>();
  } 
  /* XML文件结束解析时调用此method */
  @Override 
  public void endDocument() throws SAXException
  {
  }

  /* 解析到Element的开头时调用此method */
  @Override 
  public void startElement(String namespaceURI, String localName, 
               String qName, Attributes atts) throws SAXException
  { 
    if (localName.equals("content"))
    { 
      list.add(atts.getValue("url"));
    }
  }
  /* 解析到Element的结尾时调用此method */
  @Override 
  public void endElement(String namespaceURI, String localName,
                         String qName) throws SAXException
  {
  } 
}

