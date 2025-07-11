import { useState } from 'react'; 
import axios from "axios";
/*
{
  rua
  numero
  bairro
  cidade
  estado
  cep
  referencia
}
*/
function AddItems(props){

    const [rua, setRua] = useState("")
    const [numero, setNumero] = useState("")
    const [bairro, setBairro] = useState("")
    const [cidade, setCidade] = useState("")
    const [estado, setEstado] = useState("")
    const [cep, setCep] = useState("")
    const [referencia, setReferencia] = useState("")

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

      // const request_body = {
      //   "nome":"TESTE",
      //   "descricao":"TESTE1",
      //   "data":"2024-10-01",
      //   "horario_inicio":"22:08:28",
      //   "horario_fim": "22:08:28",
      //   "classificacao_indicativa":"1",
      //   "lotacao_maxima":200,
      //   //"endereco":
      //   "organizador":1,
      // }
      // var token = localStorage.getItem("token");
      // console.log(token);
      // const config = {
      //   headers: { Authorization: `Bearer ${token}` }
      // };

      // try {
      //   // const response = "TESTE";
      //   const response = await axios.post("http://localhost:8080/evento/", 
      //     request_body,
      //     config
      //   );
      //   console.log("Sucesso ao cadastrar Evento: ", response.data);
        
      // } catch (error) {
      //   console.error("Error signing up:", error);
      // }

    setRua("")
    setNumero("")
    setBairro("")
    setTimeout("")
    setCidade("")
    setEstado("")
    setCep("")
    setReferencia("")
    }

  return (
    <div> 
      <div className='container'>
        <div className='row'>
          <h2>Adicionar Local</h2>
        </div>
        <div className='row'>
          <label>Rua: </label>
          <input id="name-field" className='form-control' type="text" value={rua} onChange={ (e) => setRua(e.target.value) }/>
        </div>          
        <div className='row'>
          <label>Número: </label>
          <input id="description-field" className='form-control' type="text" value={numero} onChange={ (e) => setNumero(e.target.value) }/>
        </div>  
        <div className='row'>
          <label>Bairro: </label>
          <input id="date-field" className='form-control' type="text" value={bairro} onChange={ (e) => setBairro(e.target.value)}/>
        </div>       
        <div className='row'>
          <label>Cidade: </label>
          <input id="type-field" className='form-control' type="text" value={cidade} onChange={ (e) => setCidade(e.target.value) }/>
        </div>       
        <div className='row'>
          <label>Estado: </label>
          <input id="type-field" className='form-control' type="text" value={estado} onChange={ (e) => setEstado(e.target.value) }/>
        </div>    
        <div className='row'>
          <label>CEP: </label>
          <input id="type-field" className='form-control' type="text" value={cep} onChange={ (e) => setCep(e.target.value) }/>
        </div>     
        <div className='row'>
          <label>Referência: </label>
          <input id="type-field" className='form-control' type="text" value={referencia} onChange={ (e) => setReferencia(e.target.value) }/>
        </div>
        <div className='row'>
          <button type="button" className='btn btn-dark mt-3' onClick={addItemsButtonPressed}>Adicionar</button>
        </div>
      </div>
    </div>
  )
}

export default AddItems;