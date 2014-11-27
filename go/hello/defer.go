package main

import (
    "fmt"
    "time"
)


func main() {
    tm, err := time.Parse("2006-01-02 15:04:05", "2004-08-15 16:23:42")
    //tm, err := time.Parse("stdLongYear-stdZeroMonth-stdZeroDay stdHour:stdZeroMinute:stdZeroSecond", "2004-08-15 16:23:42")
    if err != nil {
        panic(err)
    }
    fmt.Println(tm)
}
