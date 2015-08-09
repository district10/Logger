Logger
======

## Libs

* Boost
* Qt4


## Usages

``` cpp
Logger::log( ) << 3 << "is three.";
Logger::log( 8 ) << "emphasized log."; // 0..9
Logger::log( BCD::LMS::CONNECTION_ERROR, QString("some optional remarks") );
Logger::log( BCD::LMS::CONNECT, "this works too" );
```


## Output Sample

|   INDEX    |        TIMESTAMP        | LEVEL |    TYPE    |       ACTION        |                 REMARKS                  |
| :--------: | :---------------------: | :---: | :--------: | :-----------------: | :--------------------------------------: |
|          1 | 2015/08/09 22:35:23:114 |   1   |  SP20000C  | stop getting image  |                                          |
|          2 | 2015/08/09 22:35:24:652 |   1   |  SP20000C  | start getting image |                                          |
|          3 | 2015/08/09 22:35:28:696 |   1   |     UR     | stop getting image  |                                  nicenec |
|          4 | 2015/08/09 22:35:30:644 |   1   |    LMS     | turn on READING     |                                          |
|          5 | 2015/08/09 22:35:31:323 |   1   |    LMS     | turn off READING    |                                          |
|          6 | 2015/08/09 22:35:35:066 |   1   |    LMS     | turn on READING     |                         thread1-01-00001 |
|          7 | 2015/08/09 22:35:35:066 |   1   |    LMS     | turn on READING     |                         thread1-01-00002 |
|          8 | 2015/08/09 22:35:35:067 |   1   |    LMS     | turn on READING     |                         thread1-01-00003 |
|          9 | 2015/08/09 22:35:35:067 |   1   |    LMS     | turn on READING     |                         thread1-01-00004 |
|         10 | 2015/08/09 22:35:35:068 |   1   |    LMS     | turn on READING     |                         thread1-01-00005 |
|         11 | 2015/08/09 22:35:35:068 |   1   |    LMS     | turn on READING     |                         thread1-01-00006 |

src:

``` plain
|   INDEX    |        TIMESTAMP        | LEVEL |    TYPE    |       ACTION        |                 REMARKS                  |
| :--------: | :---------------------: | :---: | :--------: | :-----------------: | :--------------------------------------: |
|          1 | 2015/08/09 22:35:23:114 |   1   |  SP20000C  | stop getting image  |                                          |
|          2 | 2015/08/09 22:35:24:652 |   1   |  SP20000C  | start getting image |                                          |
|          3 | 2015/08/09 22:35:28:696 |   1   |     UR     | stop getting image  |                                  nicenec |
|          4 | 2015/08/09 22:35:30:644 |   1   |    LMS     | turn on READING     |                                          |
|          5 | 2015/08/09 22:35:31:323 |   1   |    LMS     | turn off READING    |                                          |
|          6 | 2015/08/09 22:35:35:066 |   1   |    LMS     | turn on READING     |                         thread1-01-00001 |
|          7 | 2015/08/09 22:35:35:066 |   1   |    LMS     | turn on READING     |                         thread1-01-00002 |
|          8 | 2015/08/09 22:35:35:067 |   1   |    LMS     | turn on READING     |                         thread1-01-00003 |
|          9 | 2015/08/09 22:35:35:067 |   1   |    LMS     | turn on READING     |                         thread1-01-00004 |
|         10 | 2015/08/09 22:35:35:068 |   1   |    LMS     | turn on READING     |                         thread1-01-00005 |
|         11 | 2015/08/09 22:35:35:068 |   1   |    LMS     | turn on READING     |                         thread1-01-00006 |
```