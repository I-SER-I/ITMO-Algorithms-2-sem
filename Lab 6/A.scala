import java.io._
import scala.io.Source

object search1 extends App {
  val file = Source.fromFile("search1.in")
  var input = file.mkString("").split("\r\n")
  val output = new PrintWriter(new File("search1.out"))
  var ans = ""
  var counter = 0
  var i = 0
  while (i <= input(1).length - input(0).length) {
    if (input(0).equals(input(1).substring(i, i + input(0).length))) {
      counter += 1
      ans = ans + s"${i + 1} "
    }
    i += 1
  }
  output.write(s"$counter\n" + ans)
  output.close()
}