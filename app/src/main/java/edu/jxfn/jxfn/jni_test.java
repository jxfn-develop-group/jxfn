package edu.jxfn.jxfn;

/**
 * Created by laxect on 7/12/17.
 */

public class jni_test {
    static {
        System.loadLibrary("native-lib");
    }
    public static native String JniHelloWorld();
}
