//
// Copyright (C) 2018 Pharap (@Pharap)
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

using System;
using System.IO;

namespace AngleGenerator
{
    class Program
    {
        static void Main(string[] args)
        {
            double Tau = (Math.PI * 2);
            int steps = 32;

            using (var writer = new StreamWriter("Values.txt"))
                for (int index = 0; index < steps; ++index)
                {
                    double d = (((double)index / (double)steps) * Tau);
                    double x = Math.Cos(d);
                    double y = Math.Sin(d);

                    string line = string.Format("Vector2({0:0.0000}, {1:0.0000}),", x, y);

                    writer.WriteLine(line);
                    Console.WriteLine(line);
                }
            Console.ReadKey();
        }
    }
}