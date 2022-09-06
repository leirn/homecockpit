# Connection between electronical components and arduinos

There will be two arduinos mega, numbered 1 and 2

| Type     | Description                        | Arduino | Port |
|----------|------------------------------------|---------|------|
| Led      | Left pump led                      | 1       | D22  |
| Switch   | Left pump sw                       | 1       | D23  |
| Led      | Right pump led                     | 1       | D24  |
| Switch   | Right pump sw                      | 1       | D25  |
| Led      | Carb. heat led                     | 1       | D26  |
| Switch   | Carb. heat sw                      | 1       | D27  |
| Led      | Pitot heat led                     | 1       | D28  |
| Switch   | Pitot heat sw                      | 1       | D29  |
| Led      | Anti-ice led                       | 1       | D30  |
| Switch   | Anti-ice sw                        | 1       | D31  |
| Led      | BCN light led                      | 1       | D32  |
| Switch   | BCN light sw                       | 1       | D33  |
| Led      | LAND light led                     | 1       | D34  |
| Switch   | LAND light sw                      | 1       | D35  |
| Led      | TAXI light led                     | 1       | D36  |
| Switch   | TAXI light sw                      | 1       | D37  |
| Led      | NAV light led                      | 1       | D38  |
| Switch   | NA light sw                        | 1       | D39  |
| Led      | STRB light led                     | 1       | D40  |
| Switch   | STRB light sw                      | 1       | D41  |
| Led      | RED landing gear led               | 1       | D42  |
| Led      | GREEN left landing gear led        | 1       | D43  |
| Led      | GREEN front landing gear led       | 1       | D44  |
| Led      | GREEN right landing gear led       | 1       | D45  |
| Switch   | Landing gear sw                    | 1       | D46  |
| Led      | FLAP 0 led                         | 1       | D47  |
| Led      | FLAP 1 led                         | 1       | D46  |
| Led      | FLAP 2 led                         | 1       | D49  |
| Led      | FLAP FULL led                      | 1       | D50  |
| Switch   | Flap up sw                         | 1       | D51  |
| Switch   | Flap down sw                       | 1       | D52  |
| Matrix   | Column 1                           | 2       | D22  |
| Matrix   | Column 2                           | 2       | D23  |
| Matrix   | Column 3                           | 2       | D24  |
| Matrix   | Column 4                           | 2       | D25  |
| Matrix   | Column 5                           | 2       | D26  |
| Matrix   | Column 6                           | 2       | D27  |
| Matrix   | Column 7                           | 2       | D28  |
| Matrix   | Column 8                           | 2       | D29  |
| Matrix   | Row 1                              | 2       | D30  |
| Matrix   | Row 2                              | 2       | D31  |
| Matrix   | Row 3                              | 2       | D32  |
| Matrix   | Row 4                              | 2       | D33  |
| Matrix   | Row 5                              | 2       | D34  |
| Matrix   | Row 6                              | 2       | D35  |
| Matrix   | Row 7                              | 2       | D36  |
| Matrix   | Row 8                              | 2       | D37  |

## Push button matrix

To limit the number of inputs, most push up buttons on the G1000 interface will be mapped into a 8x8 grid, where a row/column pair will encode for 1 button.

|        | Column 1 | Column 2 | Column 3 | Column 4 | Column 5 | Column 6 | Column 7 | Column 8 |
|--------|----------|----------|----------|----------|----------|----------|----------|----------|
| Row 1  | PFD FN 1 | PFD FN 2 | PFD FN 3 | PFD FN 4 | PFD FN 5 | PFD FN 6 | PFD FN 7 | PFD FN 8 |
| Row 2  | PFD FN 9 | PFD FN 10 | PFD FN 11 | PFD FN 12 | MFD FN 1 | MFD FN 2 | MFD FN 3 | MFD FN 4 |
| Row 3  | MFD FN 5 | MFD FN 6 | MFD FN 7 | MFD FN 8 | MFD FN 9 | MFD FN 10 | MFD FN 11 | MFD FN 12 |
| Row 4  |          |          |          |          |          |          |          |          |
| Row 5  |          |          |          |          |          |          |          |          |
| Row 6  |          |          |          |          |          |          |          |          |
| Row 7  |          |          |          |          |          |          |          |          |
| Row 8  |          |          |          |          |          |          |          |          |
