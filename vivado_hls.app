<project xmlns="com.autoesl.autopilot.project" top="sha_init" name="Arq-2-SHA">
    <files>
        <file name="Arq-2-SHA/sha.cpp" sc="0" tb="false" cflags=""/>
        <file name="Arq-2-SHA/sha.h" sc="0" tb="false" cflags=""/>
        <file name="Arq-2-SHA/sha_sysc.cpp" sc="0" tb="false" cflags=""/>
        <file name="Arq-2-SHA/sha_sysc.h" sc="0" tb="false" cflags=""/>
        <file name="../sha_driver.cpp" sc="0" tb="1" cflags=""/>
    </files>
    <includePaths/>
    <libraryPaths/>
    <Simulation argv="input_large.asc &gt; output_large.txt">
        <SimFlow name="csim" ldflags="" csimMode="0" lastCsimMode="0"/>
    </Simulation>
    <solutions xmlns="">
        <solution name="solution1" status="active"/>
    </solutions>
</project>

