from series import SeriesMmap

DATA_MAGNETIC = SeriesMmap("data.M.bin", "!Qfff")
DATA_FLIGHT = SeriesMmap("data.F.bin", "!Qffffff")
DATA_POWER = SeriesMmap("data.P.bin", "!Qff")
DATA_ATMO = SeriesMmap("data.T.bin", "!Qff")
DATA_CONTROL = SeriesMmap("data.c.bin", "!QBBBBB")
DATA_GPS = SeriesMmap("data.G.bin", "!QffffffB")

DATA_ALL = [
	DATA_MAGNETIC,
	DATA_FLIGHT,
	DATA_POWER,
	DATA_ATMO,
	DATA_CONTROL,
	DATA_GPS,
]