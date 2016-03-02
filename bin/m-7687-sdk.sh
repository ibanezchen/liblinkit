SRC_LIBS="\
	$SRC/project/mt7687_hdk/apps/lwip_socket/GCC/Build
	"
SRC_INCS="\
	$SRC/driver/board/mt76x7_hdk/inc	\
	$SRC/middleware/third_party/lwip/src/include/	\
	$SRC/middleware/third_party/lwip/ports/include/	\
	$SRC/middleware/MTK/nvdm/inc/	\
	$SRC/middleware/MTK/nvram/inc/ \
	$SRC/driver/chip/inc/ \
	$SRC/driver/chip/mt7687/inc/	\
	$SRC/driver/CMSIS/Device/MTK/mt7687/Include/ \
	$SRC/driver/CMSIS/Include/	\
	$SRC/driver/chip/mt7687/inc \
	$SRC/kernel/service/inc
	"

for s in $SRC_LIBS ; do
	echo $s
	cp $s/*.a lib
done

rm -rf include/*
for s in $SRC_INCS ; do
	echo $s
	cp -r $s/* include
done


