# 自作OS(仮称)

## 開発環境
OS : Linux(CentOS7.1)  
使用プログラミング言語 : C, GNU Assembler  
GCC バージョン : gcc version 6.3.0  

## 記事毎に使用したソースコードをまとめておきます。
1. [OSを自作してみる1 ～Linuxで自作OSを作る環境を構築する～](http://shadows.dip.jp/?p=118)  
  
  
2. [OSを自作してみる2 ～32ビットOSの作成～](http://shadows.dip.jp/?p=126)  
   ソースコード : [version_1](/version_1)
  
3. [OSを自作してみる3 ～キーボード入力～](http://shadows.dip.jp/?p=235)  
   ソースコード : [version_2](/version_2)
  
4. [OSを自作してみる4 ～GDT初期化～](http://shadows.dip.jp/?p=337)  
   ソースコード : [version_3](/version_3)
  
5. [OSを自作してみる5 ～IDT/PICの初期化～](http://shadows.dip.jp/?p=415)  
   ソースコード : [version_4](/version_4)  

6. [OSを自作してみる6 ～割り込み経由でのキー入力～](http://shadows.dip.jp/?p=508)  
   ソースコード : [version_5](/version_5)  

7. [OSを自作してみる7 ～キーボード入力2～](http://shadows.dip.jp/?p=667)  
   ソースコード : [version_6](/version_6)  

8. [OSを自作してみる8 ～簡易libc(printfなど)を自作 & メモリマップ取得～](http://shadows.dip.jp/?p=711)  
   ソースコード : [version_7](/version_7)  
  
9. [OSを自作してみる9 ～簡易プロンプトとコマンドを実装～](http://shadows.dip.jp/?p=1077)  
   ソースコード : [version_8](/version_8)
  

## コンパイル済イメージファイル
最新版のイメージファイルを以下に配置しておきます。  
   [myos.iso](/imgfile)  

  
## 参考資料
[OSDev.org](http://wiki.osdev.org/Main_Page)  
[０から作るソフトウェア開発](http://softwaretechnique.jp/OS_Development/scratchbuild.html)  
[30日でできる！　OS自作入門](https://books.google.co.jp/books/about/30%E6%97%A5%E3%81%A7%E3%81%A7%E3%81%8D%E3%82%8B_OS%E8%87%AA%E4%BD%9C%E5%85%A5%E9%96%80.html?id=ilSvAgAAQBAJ&source=kp_cover&redir_esc=y)  
[OSのようなもの](http://d.hatena.ne.jp/wocota/searchdiary?word=%2A%5B%BC%AB%BA%EEOS%5D)  
[システムコールの呼び出し方メモ](https://qiita.com/kure/items/5a1a114f9a37aeab255c)  
[x86_64環境でシステムコールを発行する](http://sugawarayusuke.hatenablog.com/entry/2016/04/22/213251)    

<center><img src="http://shadows.dip.jp/wp-content/uploads/2017/09/githubへ投稿.png" alt="" width="30%"/></center>