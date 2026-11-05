# Build and Run Each ML8_svm Example with g++

Run these commands in the VS Code PowerShell terminal while it is in the `examples` folder.

First, collect the library source files. Run this once in the same terminal before Examples 2 through 8:

```powershell
$libSrc = (Get-ChildItem ..\src\*.cpp).FullName
```

## Example 1: Load a CSV

```powershell
g++ -std=c++17 -I ..\include example1_load_csv.cpp ..\src\dataset.cpp -o example1_load_csv.exe
.\example1_load_csv.exe ..\data\input\linear_separable.csv
```

## Example 2: Compare scaling methods

```powershell
g++ -std=c++17 -I ..\include example2_scaling.cpp $libSrc -o example2_scaling.exe
.\example2_scaling.exe
```

## Example 3: Show the hyperplane and margins

```powershell
g++ -std=c++17 -I ..\include example3_margin.cpp $libSrc -o example3_margin.exe
.\example3_margin.exe
```

## Example 4: Train and predict

```powershell
g++ -std=c++17 -I ..\include example4_train_predict.cpp $libSrc -o example4_train_predict.exe
.\example4_train_predict.exe ..\data\input\linear_separable.csv
```

## Example 5: Run the full pipeline

The predictions CSV is saved in the Windows Temp folder.

```powershell
$outputCsv = Join-Path $env:TEMP ("ml8_predictions_" + [guid]::NewGuid().ToString("N") + ".csv")
g++ -std=c++17 -I ..\include example5_full_pipeline.cpp $libSrc -o example5_full_pipeline.exe
.\example5_full_pipeline.exe ..\data\input\linear_separable.csv "$outputCsv"
```

## Example 6: Display the training loss curve

```powershell
g++ -std=c++17 -I ..\include example6_loss_curve.cpp $libSrc -o example6_loss_curve.exe
.\example6_loss_curve.exe
```

## Example 7: Find support vectors

```powershell
g++ -std=c++17 -I ..\include example7_support_vectors.cpp $libSrc -o example7_support_vectors.exe
.\example7_support_vectors.exe ..\data\input\linear_separable.csv
```

## Lambda sweep

The results CSV is saved in the Windows Temp folder.

```powershell
$outputCsv = Join-Path $env:TEMP ("ml8_lambda_" + [guid]::NewGuid().ToString("N") + ".csv")
g++ -std=c++17 -I ..\include lambda_sweep.cpp $libSrc -o lambda_sweep.exe
.\lambda_sweep.exe ..\data\input\linear_separable.csv "$outputCsv"
```
