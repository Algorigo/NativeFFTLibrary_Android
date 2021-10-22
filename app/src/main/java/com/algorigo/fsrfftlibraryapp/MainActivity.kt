package com.algorigo.fsrfftlibraryapp

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import com.algorigo.nativefft.NativeFFT

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        listOf<Any>()

        val data = listOf(
            doubleArrayOf(0.23, 0.11),
            doubleArrayOf(0.25, 0.21),
            doubleArrayOf(0.63, 0.35),
            doubleArrayOf(0.31, 0.62),
            doubleArrayOf(0.62, 0.25),
            doubleArrayOf(0.55, 0.38),
            doubleArrayOf(0.10, 0.09),
            doubleArrayOf(0.22, 0.38),
            doubleArrayOf(0.91, 0.29),
            doubleArrayOf(0.11, 0.03),
        )
        val resultC2c = NativeFFT.fftC2c(2, data)
        Log.e(LOG_TAG, "result:${resultC2c.toTypedArray().contentDeepToString()}")
        val resultAbs = NativeFFT.fftC2cAbs(2, data)
        Log.e(LOG_TAG, "result:${resultAbs.toTypedArray().contentDeepToString()}")
        val resultAbsSum = NativeFFT.fftC2cAbsSum(2, data)
        Log.e(LOG_TAG, "result:${resultAbsSum.toTypedArray().contentToString()}")
    }

    companion object {
        val LOG_TAG: String = MainActivity::class.java.simpleName
    }
}