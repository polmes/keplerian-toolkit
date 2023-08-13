from datetime import datetime, timedelta

def to_datetimes(epoch:datetime, seconds:list[float]) -> list[datetime]:
    return [ epoch + timedelta(seconds=s) for s in seconds ]
