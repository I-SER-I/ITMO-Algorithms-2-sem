File.open("prefix.in", "r") do |input|
  str = input.read()
  prefix = Array.new
  prefix[0] = 0
  (1..str.size() - 1).each do |i|
    prefix[i] = 228_228_228
  end
  k = 0
  (1..str.size() - 1).each do |i|
    k = prefix[i - 1]
    while (str[i] != str[k] and k > 0)
      k = prefix[k - 1]
    end
    if (str[i] == str[k])
      k += 1
    end
    prefix[i] = k
  end
  File.open("prefix.out", "w") do |output|
    (0..prefix.length() - 2).each do |i|
      output.write(prefix[i].to_s + " ")
    end
  end
end