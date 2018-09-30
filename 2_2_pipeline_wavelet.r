source('utils.r')
source('algorithms.r')

dataFolder     = 'data'
pipelineFolder = 'pipeline'
seriesList     = loadSeriesFile(dataFolder)

params = expand.grid(
  filters = c("haar", "d4", "d6", "d8", "d10", "d12", "d14", "d16", "d18", "d20",#Daubechies
              "la8", "la10", "la12", "la14", "la16", "la18", "la20", #Least Asymetric
              "bl14", "bl18", "bl20", #Best Localized
              "c6", "c12", "c18", "c24", "c30"), #Coiflet
  n.levels = 1:4,
  stringsAsFactors = FALSE
)

runPipeline(seriesList, waveletDec, params, pipelineFolder, 'wavelet')
