#exp2--tiny_shell_cmd_interpreter
#实验二 一个简单的shell命令解释器

可以解释以下形式的命令

cmd [[para1] [para2] ... ] [ > output_file]  [&]

cmd [[para1] [para2] ... ] [ < input_file ]  [&]

cmd1 [[para1] [para2] ... ] [ < input_file ]  | cmd2 [[para1] [para2] ... ]

以及由以上单元使用 ‘;’ 连接的多个命令
e.g.
$ ls -l > 1.txt ; cat < 1.txt | grep a ; ls -l / &
