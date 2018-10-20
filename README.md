# PixelSorter_s

## ビルド

事前にシステムかユーザーの環境変数に`LUA_LIB_PATH`を作り、Luaのライブラリとヘッダファイルのパスを登録しておくと、後々楽です。  
そうでない場合は、プロジェクトのプロパティの`C/C++ -> General -> Additional Include Directories`の`$(LUA_LIB_PATH)`をLuaのヘッダのインクルードパスに、`Linker -> General -> Additional Library Directories`の`$(LUA_LIB_PATH)`をLuaのライブラリのパスにそれぞれ変更してください。  

その後、`General -> Output Directory`をDLLを出力したい場所に変更してください。  
自分のスクリプトのフォルダなどにしておくと、ビルドするたびにDLLをコピーしなくてもよくなるので少し楽になります。

___
## スクリプト内での呼び出し
このDLLの関数は、事前に`obj.putpixeldata()`の呼び出し等の前準備を必要としません。画像の取得などの下準備から処理後のデータの仕上げまですべてDLL内で完結しています。  
実際の呼び出しは、
```lua
require("PixelSorter_s")
PixelSorter_s.PixelSort(lum, blur, dir, pSize, conf, eDir, enl, crit, bg)
```
のようになります。らくちん。

___
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
* `pNum : int`  
	ページ番号[1-2]