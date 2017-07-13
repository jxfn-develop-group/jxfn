package edu.jxfn.jxfn;

import android.graphics.Bitmap;
import android.graphics.Canvas;
import android.graphics.ColorMatrix;
import android.graphics.ColorMatrixColorFilter;
import android.graphics.Paint;

/**
 * Created by laxect on 7/12/17.
 */

public class PreProcess {
    static {
        System.loadLibrary("pre-process");
    }
    public static Bitmap RgbToGray(Bitmap bmSrc)
    {
        int width = bmSrc.getWidth();
        int height = bmSrc.getHeight();
        // 创建目标灰度图像
        Bitmap bmpGray = null;
        bmpGray = Bitmap.createBitmap(width, height, Bitmap.Config.RGB_565);
        // 创建画布
        Canvas c = new Canvas(bmpGray);
        Paint paint = new Paint();
        ColorMatrix cm = new ColorMatrix();
        cm.setSaturation(0);
        ColorMatrixColorFilter f = new ColorMatrixColorFilter(cm);
        paint.setColorFilter(f);
        c.drawBitmap(bmSrc, 0, 0, paint);
        return bmpGray;
    }


    public static String bitmapPreProcess(Bitmap bitSrc)
    {
        int x = bitSrc.getWidth();
        int y = bitSrc.getHeight();
        int[] bitmapArray = new int[x * y];
//        System.out.print(x * y);
        bitSrc.getPixels(bitmapArray, 0, x, 0, 0, x, y);
        return preProcess(bitmapArray);
    }


    public static native String preProcess(int[] arr);
}
