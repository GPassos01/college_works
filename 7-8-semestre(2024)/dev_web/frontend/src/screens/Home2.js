import React, { useState } from "react";
import styles from '../styles/home.module.css'
import { Container, Row, Col, Button } from 'react-bootstrap';


export default function LoginScreen() {

  return (
    <div>                           {/* padding y 5 pixels */}
      <section id="hero" className="py-5 text-center text-light" className={styles.section}>
      {/* <img src="https://www.guiadasemana.com.br/contentFiles/image/opt_w840h0/festa-de-faculdade-2.jpg" class="img-fluid" alt="Responsive image"/> */}
        <Container>
            <h1>Bem-vindo ao UniVento!</h1>
            <p className="lead">A plataforma para compra e venda de ingressos</p>
                            {/*secondary, sucess, danger, warning, info*/}
                                          {/*lg = large, sm = small*/}
          <Button variant="primary" size="lg">Descubra novos eventos</Button>
        </Container>
      </section>
                                          {/*background light*/}

      <section id="pricing" className="py-5">
        <Container>
          <h2 className="text-center mb-4">Destaques</h2>
          <Row>
            <Col md={4}>
              <div className="text-center p-4 border rounded">
                <h3>Evento 1</h3>
                <p>Lorem</p>
                <Button variant="primary">Saiba mais</Button>
              </div>
            </Col>
            <Col md={4}>
              <div className="text-center p-4 border rounded">
                <h3>Evento 2</h3>
                <p>Lorem</p>
                <Button variant="primary">Saiba mais</Button>
              </div>
            </Col>
            <Col md={4}>
              <div className="text-center p-4 border rounded">
                <h3>Evento 3</h3>
                <p>Lorem </p>
                <Button variant="primary">Saiba mais</Button>
              </div>
            </Col>
          </Row>
        </Container>
      </section>

      <section id="testimonials" className="py-5 bg-dark">
        <Container>
          <h2 className="text-center mb-4">Depoimentos</h2>
          <Row>
            <Col md={4}>
              <div className="text-center p-4 border rounded text-light">
                <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit.</p>
                <h5>- João Silva</h5>
              </div>
            </Col>
            <Col md={4}>
              <div className="text-center p-4 border rounded text-light">
                <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit.</p>
                <h5>- Maria Oliveira</h5>
              </div>
            </Col>
            <Col md={4}>
              <div className="text-center p-4 border rounded text-light">
                <p>Lorem ipsum dolor sit amet, consectetur adipiscing elit.</p>
                <h5>- José Santos</h5>
              </div>
            </Col>
          </Row>
        </Container>
      </section>
    </div>
  );
}