package com.changba.utils;

public class JNIUtils
{
  static
  {
    System.loadLibrary("secret");
  }

  public static native String getJiangKey(String paramString);

  public static native String getSecretKey(String paramString);

  public static native String getUserCP(String paramString1, String paramString2, String paramString3, String paramString4, String paramString5);

  public static native String getUserInfo(String paramString1, String paramString2, String paramString3);

  public static native String getUserL(String paramString1, String paramString2, String paramString3, String paramString4);

  public static native String getUserLBO(String paramString1, String paramString2, String paramString3, String paramString4, String paramString5);

  public static native String getUserR(String paramString1, String paramString2, String paramString3, String paramString4, String paramString5, String paramString6, String paramString7, String paramString8, String paramString9, String paramString10, String paramString11, String paramString12);

  public static native String giveGift(String paramString1, String paramString2, String paramString3, String paramString4, String paramString5, String paramString6, String paramString7, String paramString8, String paramString9, boolean paramBoolean, String paramString10);

  public static native boolean isCodeS(String paramString);
}
