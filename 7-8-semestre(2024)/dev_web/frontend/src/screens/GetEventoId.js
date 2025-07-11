import { useState } from 'react'; 
import axios from "axios";
/*
{
  name:
  price:
  type:
  brand:
}
*/
function AddItems(props){

    const [id, setId] = useState("")
    const [name, setName] = useState("")
    const [description, setDescription] = useState("")
    const [date, setDate] = useState("")
    const [time, setTime] = useState("")
    const [classification, setClassification] = useState("")
    const [capacity, setCapacity] = useState("")
    const [organizador, setOrganizador] = useState("")

    //funcao disparada no onclick que está la embaixo
    const addItemsButtonPressed = async () => {
      // props.addItems({
      //       "name": name,
      //       "description": description,
      //       "date" : date,
      //       "time" : time,
      //       "type": type,
      //       "classification": classification,
      //       "capacity": capacity
      //   })

        //pegar o local storage que vai ficar salvo depois que a gnt loga
        var token = localStorage.getItem("token");
        console.log(token);
        const config = { //salvar esse token dentro dessa config
          headers: { Authorization: `Bearer ${token}` }
        };

        try {
          // const response = "TESTE";
          const response = await axios.get(`http://localhost:8080/evento/${id}`, 
            // request_body,
            config
          );
          console.log("Sucesso ao cadastrar Evento: ", response.data);
          console.log(response.data);
          console.log(response.data.nome);
          setName(response.data.nome)
          setDescription(response.data.descricao)
          const dataEvento = new Date(response.data.data)
          setDate(dataEvento.toISOString().split('T')[0])
          setTime(response.data.horario_fim.join(':'))
          setClassification(response.data.classificacao_indicativa)
          setCapacity(response.data.lotacao_maxima)

        } catch (error) {
          console.error("Error signing up:", error);
        }


        //fazer uma tela para listar 

      // apaga os campos
      // setName("")
      // setDescription("")
      // setDate("")
      // setTimeout("")
      // setClassification("")
      // setCapacity("")

    }

  return (
    <div> 
      <div className='container'>
        <div className='row'>
          <h2>Requisitar Evento</h2>
        </div>
        <div className='row'>
          <label>Id do Evento: </label>
          <input id="name-field" className='form-control' type="text" value={id} onChange={ (e) => setId(e.target.value) }/>
        </div>          
        <div className='row'>
          <label>Nome do Evento: </label>
          <input disabled id="name-field" className='form-control' type="text" value={name} onChange={ (e) => setName(e.target.value) }/>
        </div>          
        <div className='row'>
          <label>Descrição: </label>
          <input disabled id="description-field" className='form-control' type="text" value={description} onChange={ (e) => setDescription(e.target.value) }/>
        </div>  
        <div className='row'>
          <label>Data: </label>
          <input disabled id="date-field" className='form-control' type="date" value={date} onChange={ (e) => setDate(e.target.value)}/>
        </div>  
        <div className='row'>
          <label>Horário: </label>
          <input disabled id="time-field" className='form-control' type="time" value={time} onChange={ (e) => setTime(e.target.value)}/>
        </div>       
        <div className='row'>
          <label>Classificação indicativa: </label>
          <input disabled id="classification-field" className='form-control' type="text" value={classification} onChange={ (e) => setClassification(e.target.value) }/>      
        </div> 
        <div className='row'>
          <label>Lotação máxima: </label>
          <input disabled id="capacity-field" className='form-control' type="text" value={capacity} onChange={ (e) => setCapacity(e.target.value) }/>      
        </div>      
        <div className='row'>
          <label>Organizador: </label>
          <input disabled id="capacity-field" className='form-control' type="text" value={organizador} onChange={ (e) => setOrganizador(e.target.value) }/>      
        </div>      
        <div className='row'>
          <button type="button" className='btn btn-dark mt-3' onClick={addItemsButtonPressed}>Ver</button>
        </div>
      </div>
    </div>
  )
}

export default AddItems;