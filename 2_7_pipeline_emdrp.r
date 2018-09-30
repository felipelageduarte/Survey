source('utils.r')
source('algorithms.r')

dataFolder     = 'data'
pipelineFolder = 'pipeline'
seriesList     = loadSeriesFile(dataFolder)

params = expand.grid(
  thresh   = seq(0.01, 0.3, by=0.025),
  detlevel = seq(0.01, 0.3, by=0.025),
  stringsAsFactors = FALSE
)
runPipeline(seriesList, emdrpDec, params, pipelineFolder, 'emdrp')
