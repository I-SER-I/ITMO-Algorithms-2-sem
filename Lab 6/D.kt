import java.io.BufferedReader
import java.io.IOException
import java.io.InputStreamReader
import java.io.PrintWriter
import java.util.*
import kotlin.Array

fun main(args : Array<String>) {
    var alphabet = next()
    var str = next()
    str += '#'
    val result: Array<Array<Int>> = Array(str.length) {Array(alphabet.toInt()) {0} }
    val pref : Array<Int> = Array(str.length) {0}
    for (i in 1 until str.length) {
        var j = pref[i - 1]
        while(j > 0 && str[i] != str[j])
            j = pref[j - 1]
        if (str[i] == str[j])
            j++;
        pref[i] = j;
    }
    for (i in str.indices) {
        for(c in 'a' until 'a' + alphabet.toInt()) {
            if (i > 0 && c != str[i])
                result[i][c - 'a'] = result[pref[i - 1]][c - 'a']
            else
                if(c == str[i])
                    result[i][c - 'a'] = i + 1
        }
    }
    for(row in result) {
        for(cell in row)
            out.print("$cell ")
        out.println()
    }
    out.close()
}

private var br = BufferedReader(InputStreamReader(System.`in`))
private var st: StringTokenizer? = null
private var out = PrintWriter(System.out)

@Throws(IOException::class)
private fun next(): String {
    while(st == null || !st!!.hasMoreTokens())
        st = StringTokenizer(br.readLine())
    return st!!.nextToken()
}

@Throws(IOException::class)
private fun nextInt(): Int {
    return next().toInt()
}