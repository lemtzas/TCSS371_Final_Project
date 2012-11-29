SEPARATOR = "----------------------------------------------------"

puts ":::" + Dir.pwd + ":::"


all_files = Dir.new(".").each.sort
files = Array.new

#headers
all_files.each do |f|
  if f =~ /.*\.h$/
    files.push(f)
  end
end

#sources
all_files.each do |f|
  if f =~ /.*\.c$/
    files.push(f)
  end
end

puts files


output = File.open("./submission.txt", "w+")


header = File.open("./header.txt")
header.readlines.each do |l|
  output.puts l
end
header.close
files.each do |f|
  file = File.open(f)
  output.puts SEPARATOR
  output.puts "// #{f}"
  output.puts ""
  file.readlines.each do |l|
    output.puts l
  end
  file.close
end

output.puts SEPARATOR
output.puts "// The output"
File.open("./output.txt").readlines.each do |l|
  output.puts l
  output.puts ""
end

output.close

gets.chomp