package com.example.airsync; 

/* import���class */
import java.util.ArrayList;
import java.util.List;
import org.xml.sax.Attributes; 
import org.xml.sax.SAXException; 
import org.xml.sax.helpers.DefaultHandler; 
/*
 * ��xml�ļ��е���Ƭ��Ϣ��������
 */
public class PhotoHandler extends DefaultHandler
{
  private List<String> list;
  /*������Ƭ��Ϣ */
  public List<String> getPhotos()
  { 
    return list;
  }

  /* XML�ļ���ʼ����ʱ���ô�method */
  @Override 
  public void startDocument() throws SAXException
  { 
    list = new ArrayList<String>();
  } 
  /* XML�ļ���������ʱ���ô�method */
  @Override 
  public void endDocument() throws SAXException
  {
  }

  /* ������Element�Ŀ�ͷʱ���ô�method */
  @Override 
  public void startElement(String namespaceURI, String localName, 
               String qName, Attributes atts) throws SAXException
  { 
    if (localName.equals("content"))
    { 
      list.add(atts.getValue("url"));
    }
  }
  /* ������Element�Ľ�βʱ���ô�method */
  @Override 
  public void endElement(String namespaceURI, String localName,
                         String qName) throws SAXException
  {
  } 
}

