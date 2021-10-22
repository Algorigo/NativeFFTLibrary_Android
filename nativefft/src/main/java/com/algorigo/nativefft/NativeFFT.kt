package com.algorigo.nativefft

class NativeFFT {

    /**
     * A native method that is implemented by the 'nativefft' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    companion object {
        // Used to load the 'nativefft' library on application startup.
        init {
            System.loadLibrary("nativefft")
        }

        @JvmStatic
        external fun fftC2c(arrayCount: Int, values: List<DoubleArray>): List<Array<Complex>>

        @JvmStatic
        external fun fftC2cAbs(arrayCount: Int, values: List<DoubleArray>): List<DoubleArray>

        @JvmStatic
        external fun fftC2cAbsSum(arrayCount: Int, values: List<DoubleArray>): List<Double>
    }
}