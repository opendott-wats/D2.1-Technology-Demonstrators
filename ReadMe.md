---
title: D2.1 Technology Demonstrators
subtitle: Open Technology - Training and Explorations
author: Jens Alexander Ewald (ESR1)
---
# D2.1 Technology Demonstrators

![Hardware sketch using Open Hardware modules with sensors and LoRaWAN connectivity](pictures/2021-05-04_14-21-46-000❤️.jpg)

Supervised by Jayne Wallace (University of Northumbria, Newcastle upon Tyne), Mel Woods (University of Dundee), Mehan Jayasuriya (Mozilla Foundation), Max von Grafenstein (UdK Berlin), Davide Gomba (Officine Innesto).

This research has received funding from the European Union’s Horizon 2020 research and innovation program under the Marie Skłodowska-Curie grant agreement No. 813508. For more details, see [Acknowledgements section](#acknowledgements).

## Introduction

This repository documents research through design activities using [creative/craft technologist practice](https://www.journalofjewelleryresearch.org/wp-content/uploads/2022/05/0143_SMT_Vol13_P04_Shorter_FA.pdf) as a thinking through making approach to explore open technologies in relation to wearable IoT as part of the [Open Design of trusted Things - OpenDoTT](https://opendott.org) project.
The code and documentation of activities investigates potentials and possibilities of open technology for sketching and prototyping for wearable IoT, including material from an accompanying [Open Technology Training](#open-technology-training).

### Aims and Objectives

The aim of the training and explorations is to gain experience with open technology in the scope of wearables in order to develop capacity to shape emerging best practices in relation to internet connected technology when it intersects with our bodies and sense of self. The insights will inform further prototype development and the role of open technology with the wider research project on the relationship of wearables and the self. Through a series of code sketches and partial prototypes the addresses research questions such as:

- How to make a wearable using readily available open technology hardware and software?
- How to make an open technology wearable IoT connecting directly to the internet?
- What data/sensors in relation to the body and the self are meaningful for a craft/creative technologist approach?
- How can craft tech practice engage in open technology?
- What challenges emerge when approaching open technology through craft technologist practice?
- In which ways can the notion of "open" manifest when exploring digital technology in relation to the body?

## Open Technology Training

The `/training` directory contains sketches as well as external examples used in and/or written during the Open Technology Training. The training aimed to provide a foundation for further explorations particular to each OpenDoTT area (body/self, home, communities and neighborhoods, smart city, and a trust mark for IoT).
Additionally, through individual training sessions I was able to explore LoRaWAN technology (low range wide area network). Details can be found in the relevant project directories' README files.

## Explorations on making a wearable IoT piece

The `/explorations` directory contains code sketches documenting my thinking through making approach. In this practice, for example, writing code is carried out as an investigative and reflective practice where the aim is an in-depth understanding of a wide spectrum of technology as a material matter and the making of prototypes gain further meaning than proofs or solutions.

The different projects/sketches build in part on the training insights building a working piece of wearable IoT.

`/explorations/LoRa/` contain a simple LoRaWAN test sketch which enabled me to experience and explore the viability of this firstly intriguing connectivity topology. The place where I have resided during this time had LoRaWAN coverage through [The Things Network](https://www.thethingsnetwork.org/). This was particularly insightful as it showed that real world sizes of payloads are indeed minimal and low in spectrum sharing capacity, which makes it nearly unsuitable for sketching in research through design and thinking through making scenarios.

`/explorations/the-drawing-things` contains code sketches which use statically exported step count data (from the researcher's phone) to explore different modes of making this data available in an interactive drawing process (generating "ink" from body related data). This approach of "drawing with data" as a semi-automatic tangible reflective non-verbal conversation with data of our bodies is preliminary work to the prototype "The Drawing Thing" which is also deployed with participant as part of WP2. For easy sharing of iterations sketches use web based technology and for code accessibility they build on the popular and openly available [p5js](https://p5js.org) platform.

`/explorations/the-other-things` contains firmware studies in building a step count tracker myself using open(-ly available) technologies. The sketches use the well known open platform Arduino as well as explore the Circuit Python platform with the benefit of distributing firmware updates as simple files which participants can drag and drop on the devices connected through USB on their own machines. This option was considered to enable remote studies, which are common during the Covid-19 pandemic.
The main insight from these explorations is that making a device which is accurate enough as well as sufficiently compact and concise in footprint is a challenge which is time-consuming, less design related, and already solved by industry products. The latter have the disadvantage of not being open (in the sense of open technology), for which we suggest approaching them through "uncrafting" (Murer et al.), shifting "open" technology to "opening technology". Alternatively, ready-made products have the advantage to be familiar to participants which could potentially benefit primary focus on relationships to data.

## Licenses

Source code newly written by the researcher in this repository is licensed under
the GNU Public License (GPL).

[![Creative Commons License](https://i.creativecommons.org/l/by-sa/4.0/88x31.png)](http://creativecommons.org/licenses/by-sa/4.0/)

Any other original content is licensed under a [Creative Commons Attribution-ShareAlike 4.0 International License](http://creativecommons.org/licenses/by-sa/4.0/).

## Acknowledgements

Doctoral Researcher: [Jens Alexander Ewald](mailto:jens.a.ewald@northumbria.ac.uk)

Supervisors: Jayne Wallace (University of Northumbria, Newcastle upon Tyne), Mel Woods (University of Dundee), Mehan Jayasuriya (Mozilla Foundation), Max von Grafenstein (UdK Berlin), Davide Gomba (Officine Innesto)

This project is part of [Open Design of Trusted Things (OpenDoTT) doctoral training network](https://opendott.org.) and has received funding from the European Union’s Horizon 2020 research and innovation program under the Marie Skłodowska-Curie grant agreement No. 813508.
