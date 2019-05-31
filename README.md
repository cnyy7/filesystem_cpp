# filesystem_cpp
模拟文件系统

支持的命令如下：

- 初始化                        						format
- 查看当前目录下文件列表                 dir
- 查看文件信息                                    cat            (cat + 文件名)  
- 查看系统空间使用信息                     ls    
- 创建目录                                            md           (md  + 目录名)  
- 创建文件                                            touch       (touch  + 文件名 + 文件长度 + 权限)
- 删除文件                                            del            (del + 文件名) 
- 打开文件                                            open        (open + 文件名) 
- 导出文件                                            export      (export + 文件名 + 要导出的地址) 
- 更改文件名字                                     rename   (rename + 文件名 + 新文件名) 
- 导入文件                                            import      (import + 要导入的文件) 
- 打开文件                                            open         (open + 文件名) 
- 关闭文件                                            close         (close + 文件名) 
- 读取文件                                            read          (read + 文件名) 
- 写入文件                                            write         (write + 文件名 + 写入方式(0:覆盖，大于1：追加))
- 复制文件                                            copy          (copy + 文件名）  
- 移动文件                                            move        (move + 文件名）  
- 粘贴文件                                            paste        (paste + 文件名)  
- 删除目录                                            rd              (rd + 目录名)
- 更改文件权限                                    attrib        (attrib + 目录名+权限（r,o,w）)
- 进入当前目录下的指定目录             cd              (cd + 目录名)
- 返回上一级目录                                cd..  
- 显示时间                                            time  
- 显示系统信息                                    ver  
- 显示帮助命令                                    help  
- 退出文件系统                                    exit  
- 退出登录                                            logout