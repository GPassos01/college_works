import React, { useState, useEffect } from "react";
import { useParams } from "react-router-dom";
import axios from "axios";

export default function GetEventoAll(){
    const [eventos, setEventos] = useState([]);
    const [data, setData] = useState(() => {
        const fetchData = async () => {
            try{
                var token = localStorage.getItem("token");
                console.log(token);
                const config = { //salvar esse token dentro dessa config
                    headers: { Authorization: `Bearer ${token}` }
                };
                const response = await axios.get(`http://localhost:8080/evento/`,
                    config
                );
                console.log(response.data);
                // console.log(response.data.data[0]);
                setEventos(response.data);
            }
            catch(ex){
                console.error("Error fetching data: ", ex);
            }
        };
        return fetchData();   
    });

    const showItems = (item) =>{
        return(
            <tr>
                <td> {item.nome}</td>
                <td> {item.descricao}</td>
                <td> {item.data}</td>
                <td> {item.horario_inicio}</td>
                <td> {item.horario_fim}</td>
                <td> {item.classificacao_indicativa}</td>
                <td> {item.lotacao_maxima}</td>
            </tr>
        )
    } 

    return (
        <div className='container'>
            <div className='row'>
                <h2>Eventos</h2>
            </div>
            <div className='row'>
                <table className='table table-striped'>
                    <thead>
                        <tr>
                        <th scope='col'>Nome</th>
                        <th scope='col'>Descrição</th>
                        <th scope='col'>Data</th>
                        <th scope='col'>Hora Inicio</th>
                        <th scope='col'>Hora Fim</th>
                        <th scope='col'>Classificação</th>
                        <th scope='col'>Lotacao</th>
                        </tr>
                    </thead>

                    <tbody>{eventos.map(showItems)}</tbody>
                </table>
            </div>
        </div>
    )

}