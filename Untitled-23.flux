from(bucket: "telegraf/autogen")
    |> range(start: -10s)
    |> filter(fn: (r) => r["_measurement"] == "disk")