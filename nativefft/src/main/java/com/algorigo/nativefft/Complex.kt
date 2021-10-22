package com.algorigo.nativefft

data class Complex(val real: Double, val img: Double) {
    override fun toString(): String {
        return "$real ${img}j"
    }
}
