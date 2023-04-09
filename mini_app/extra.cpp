            f(i,j) = -(4. + alpha) * s(i,j)
                        + s(i-1, j) + s(i+1, j)
                        + s(i, j-1) + s(i,j+1)
                        + beta * s(i,j) * (1 - s(i,j))
                        + alpha * y_old(i,j);