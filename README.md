# PixelSorter_s
![Packagist](https://img.shields.io/packagist/l/doctrine/orm.svg)
## ビルド

`MSBuild.exe`にパスが通っていることが前提です。
`cmake_batch.sh`の`cmake_install_path`にdllとanmファイルをインストールするパスを、
`lua_include_dir`に`lua.hpp`があるパスを、
`lua_library_dir`に`lua51.lib`があるパスを入れてください。  
`build`ディレクトリを作って入り、
```sh
../cmake_batch.sh msvc
```
でプロジェクトを生成します。
そのまま
```sh
../msvc_build.sh install
```
で、ビルド時にエラーが起きなければ`cmake_install_path`で指定したディレクトリに`PixelSorter_s.dll`と
`PixelSorter_s.anm`がインストールされます。


## スクリプト内での呼び出し
このDLLの関数は、事前に`obj.putpixeldata()`の呼び出し等の前準備を必要としません。画像の取得などの下準備から処理後のデータの仕上げまですべてDLL内で完結しています。  
実際の呼び出しは、
```lua
require("PixelSorter_s")
PixelSorter_s.PixelSort(lum, blur, dir, pSize, conf, eDir, enl, crit, bg)
```
のようになります。らくちん。


## 関数
このDLLモジュールに含まれている関数です。

```lua
PixelSort(lum, blur, dir, pSize, conf, eDir, enl, crit, bg)
```
PixelSorterのメインの関数です。これを呼び出すとPixel Sortのエフェクトがかかった状態になります
#### 引数
* `lum : int`  
    基準にする輝度
* `blur : int`  
    基準の輝度からの相対的な範囲
* `dir : int`  
    ソートする方向
* `pSize : int`  
    ソートするピクセルのサイズ  
    大きくするとモザイクのようになる
* `conf : boolean`  
    ソート対象のピクセルが緑になる  
    主に範囲の確認用
* `eDir : int`  
    画像を引き延ばす方向
* `enl : float`  
    画像の引き延ばし(%)  
    100%にすると一番端のピクセルのみになる
* `crit : int`  
    ソートの基準式  
    1.Luminance (輝度基準)  
    2.Average (RGBの平均)  
    3.Multiply (正規化したRGBを乗算)  
    4.Min (RGBの最小値)  
    5.Max (RGBの最大値)  
    6.XOR (RGBでXOR演算)
* `bg : int(bool)`  
    元画像の合成

```lua
Instructions(pNum)
```
スクリプトの説明書を描画します。
#### 引数
* `pNum : int`  
    ページ番号[1-2]
