areaTri a b c = c * h / 2
    where   
        cosAlpha = (b^2 + c^2 - a^2) / (2*b*c)
        sinAlpha = sqrt (1 - cosAlpha^2)
        h = b*sinAlpha